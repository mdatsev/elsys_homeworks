#define WAITING_ZOMBIES 1

#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "ui.h"

int zombies = 1,
	soliders = 0,
	health = 100,
	gold = 100;
pthread_mutex_t gold_mutex = PTHREAD_MUTEX_INITIALIZER,
				soliders_mutex = PTHREAD_MUTEX_INITIALIZER,
				zombies_mutex = PTHREAD_MUTEX_INITIALIZER;
#if WAITING_ZOMBIES
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
#endif
bool modify_gold(int amount)
{
	pthread_mutex_lock(&gold_mutex);
	if (gold + amount < 0)
	{
		print_fail("Not enough gold!");
		pthread_mutex_unlock(&gold_mutex);
		return false;
	}
	gold += amount;
#if WAITING_ZOMBIES
	if (gold >= 100)
		pthread_cond_signal(&cond);
#endif
	print_gold(gold);
	pthread_mutex_unlock(&gold_mutex);
	return true;
}

void *miner(void *_)
{
	for (;;)
	{
		modify_gold(10);
		sleep(1);
	}
	return 0;
}

void create_miner()
{
	if (!modify_gold(-100))
		return;
	print_msg("Miner created!");
	pthread_t _;
	pthread_create(&_, NULL, &miner, NULL);
}

void create_soliders(int amount)
{
	if (!modify_gold(-10 * amount))
		return;
	pthread_mutex_lock(&soliders_mutex);
	soliders += amount;
	print_soldiers(soliders);
	pthread_mutex_unlock(&soliders_mutex);
	if (amount == 1)
		print_msg("Solider created!");
	else
		print_msg("10 x soldiers created!"); //todo
}

void *zombies_worker(void *_)
{
	for (;;)
	{
#if WAITING_ZOMBIES
		pthread_mutex_lock(&gold_mutex);
		while (gold < 100)
			pthread_cond_wait(&cond, &gold_mutex);
		pthread_mutex_unlock(&gold_mutex);
#endif
		for (int i = 5; i >= 0; i--)
		{
			pthread_mutex_lock(&zombies_mutex);
			print_zombies(i, zombies);
			pthread_mutex_unlock(&zombies_mutex);
			sleep(1);
		}
		pthread_mutex_lock(&soliders_mutex);
		if (zombies > soliders)
		{
			health -= zombies - soliders;
			print_health(health);
			print_fail("Zombie attack succeded ;(!");
			if (health <= 0)
				game_end(zombies);
		}
		else
			print_succ("Zombie attack deflected! :)");
		pthread_mutex_unlock(&soliders_mutex);
		pthread_mutex_lock(&zombies_mutex);
		zombies *= 2;
		pthread_mutex_unlock(&zombies_mutex);
		print_zombies(0, zombies);
	}
}

void start_zombies()
{
	pthread_t _;
	pthread_create(&_, NULL, &zombies_worker, NULL);
}

int main()
{
	init();
	print_gold(gold);
	print_soldiers(soliders);
	print_health(health);
	start_zombies();
	while (1)
	{
		int ch = get_input();
		switch (ch)
		{
		case 'q':
			pthread_mutex_lock(&zombies_mutex);
			game_end(zombies);
			pthread_mutex_unlock(&zombies_mutex); //
			break;
		case 'm':
			create_miner();
			break;
		case 's':
			create_soliders(1);
			break;
		case 'x':
			create_soliders(10);
			break;
		}
	}
}
