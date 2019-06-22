#include <deque>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <exception>
#include <unordered_set>
#include <ctime>
#include <cstdlib>

template <class C, class T>
inline int findIn(const C& container, const T& value) {
	auto found = std::find(container.begin(), container.end(), value);
	return found != container.end() 
		? std::distance(container.begin(), found)
		: -1;
}

class CardGameError : public std::logic_error {
public:
	CardGameError(const std::string& string) 
		: logic_error(string) {}
};

class Card {
public:
	Card(const std::string& suit, const std::string& rank) 
		: suit_(suit), rank_(rank) {}

	std::string get_rank() const { return rank_; }
	std::string get_suit() const { return suit_; }

	bool operator==(const Card& other) const {
		return rank_ == other.rank_ && suit_ == other.suit_;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Card& card) {
		stream << card.suit_ << card.rank_;
		return stream;
	}

	class CardComparator {
	public:
		CardComparator(const std::vector<std::string>& rank_order,
			const std::vector<std::string>& suit_order)
			: rank_order_(rank_order), suit_order_(suit_order) {}
		bool operator()(const Card& a, const Card& b) {
			auto aSuitPos = findIn(suit_order_, a.suit_);
			auto bSuitPos = findIn(suit_order_, b.suit_);
			auto aRankPos = findIn(rank_order_, a.rank_);
			auto bRankPos = findIn(rank_order_, b.rank_);
			return aSuitPos != bSuitPos 
				? aSuitPos > bSuitPos 
				: aRankPos > bRankPos;
		}

	private:
		const std::vector<std::string> rank_order_;
		const std::vector<std::string> suit_order_;
	};

private:
	std::string rank_;
	std::string suit_;
};

class Deck {
public:
	size_t size() const { return cards_.size(); }

	Card draw_top_card() {
		Card top = top_card();
		cards_.pop_front();
		return top;
	}

	Card draw_bottom_card() {
		Card bottom = bottom_card();
		cards_.pop_back();
		return bottom;
	}

	Card top_card() const {
		assure_size(1);
		return cards_.front();
	}

	Card bottom_card() const {
		assure_size(1);
		return cards_.back();
	}

	void shuffle() {
		std::srand((unsigned int)std::time(0));
		std::random_shuffle(cards_.begin(), cards_.end(), 
			[](int i){ return std::rand() % i; });
	}

	void sort(const std::vector<std::string>& rank_order,
		const std::vector<std::string>& suit_order) 
	{
		std::sort(cards_.begin(), cards_.end(),
			Card::CardComparator(rank_order, suit_order));
	}

	Deck deal(unsigned int count) {
		assure_size(count);
		Deck dealed;
		for (unsigned int i = 0; i < count; i++) {
			dealed.add(draw_top_card());
		}
		return dealed;
	}

	void add(const Card& card) { cards_.push_back(card); }


	void assure_size(unsigned int size) const
	{
		if (cards_.size() < size)
			throw CardGameError("ERROR: Not enough cards in deck");
	}

	void insert_valid_cards(const Deck& deck,
		const std::vector<std::string>& allowed_ranks,
		const std::vector<std::string>& allowed_suits) 
	{
		std::copy_if(deck.cards_.begin(), deck.cards_.end(),
			std::back_inserter(cards_), 
			[&](const Card& card) {
				return findIn(allowed_ranks, card.get_rank()) != -1 &&
					findIn(allowed_suits, card.get_suit()) != -1;
			});
	}

	friend std::istream& operator>>(std::istream& stream, Deck& deck) {
		std::string line;
		std::getline(stream, line);
		std::istringstream cards_stream(line);
		std::string card_string;
		for (int i = 0; std::getline(cards_stream, card_string, ' '); i++) {
			std::string suit(1, card_string[0]);
			std::string rank = card_string.substr(1);
			deck.cards_.emplace_back(suit, rank);
		}
		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Deck& deck) {
		for (unsigned int i = 0; i < deck.cards_.size(); i++) {
			stream << deck.cards_[i] << " ";
		}
		return stream;
	}

private:
	std::deque<Card> cards_;
};

class CardGame {
public:
	CardGame(const Deck& deck, 
		const std::string& name,
		unsigned int deck_size,
		unsigned int cards_per_hand,
		const std::vector<std::string>& rank_order,
		const std::vector<std::string>& suit_order = { "C", "D", "H", "S" })
		: name_(name),
			deck_size_(deck_size),
			cards_per_hand_(cards_per_hand),
			rank_order_(rank_order),
			suit_order_(suit_order) 
	{
		deck_.insert_valid_cards(deck, rank_order, suit_order);
		if (deck_.size() < deck_size)
			throw CardGameError("ERROR: Not enough cards for " + name_);
	}
	CardGame() {}
	virtual void print_deck_size() { 
		std::cout << deck_.size(); 
	}
	virtual void draw_top_card() { 
		std::cout << deck_.draw_top_card(); 
	}
	virtual void draw_bottom_card() { 
		std::cout << deck_.draw_bottom_card();
	}
	virtual void print_top_card() { 
		std::cout << deck_.top_card(); 
	}
	virtual void print_bottom_card() {
		std::cout << deck_.bottom_card();
	}
	virtual void deal() { 
		std::cout << deck_.deal(cards_per_hand_);
	}
	virtual void shuffle_deck() { 
		deck_.shuffle(); 
		std::cout << deck_;
	}
	virtual void sort_deck() {
		deck_.sort(rank_order_, suit_order_);
		std::cout << deck_;
	}

protected:
	const std::string name_;
	Deck deck_;
	std::vector<std::string> rank_order_;
	std::vector<std::string> suit_order_;
	unsigned int deck_size_;
	unsigned int cards_per_hand_;
};

class CardGameEngine {
public:
	CardGameEngine() : game_(nullptr) { setEngineCommands(); }
	~CardGameEngine() { delete game_; }

	void run() {
		keepRunning_ = true;
		std::cout << "> ";
		std::cin >> initialDeck_;
		while (keepRunning_) {
			std::string command;
			std::cout << "> ";
			std::cin >> command;
			try {
				execCommand(command);
			}
			catch (const CardGameError& e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	void stop() { keepRunning_ = false; }

	template <class G>
	void addGame(const std::string& command) {
		engine_commands_[command] = std::bind(&CardGameEngine::setGame<G>, this);
	}

	template <class G>
	void addCommand(std::string command, void (G::*function)(),
		bool has_output = true) 
	{
		game_commands_[command] = Operation<G>(function);
		if (has_output) output_commands_.emplace(command);
	}

	template <class G>
	void setGame() {
		delete game_;
		game_ = new G(initialDeck_);
	}

	void loadDefaultCommands() {
		addCommand("size", &CardGame::print_deck_size);
		addCommand("draw_top_card", &CardGame::draw_top_card);
		addCommand("draw_bottom_card", &CardGame::draw_bottom_card);
		addCommand("top_card", &CardGame::print_top_card);
		addCommand("bottom_card", &CardGame::print_bottom_card);
		addCommand("shuffle", &CardGame::shuffle_deck);
		addCommand("sort", &CardGame::sort_deck);
		addCommand("deal", &CardGame::deal);
	}

	void execCommand(const std::string& command)
	{
		if (engine_commands_.find(command) != engine_commands_.end())
			engine_commands_.at(command)();
		else if (game_commands_.find(command) != game_commands_.end()) {
			if (game_ == nullptr) 
				throw CardGameError("ERROR: No deck");
			game_commands_.at(command)(game_);
		}
		else
			throw CardGameError("ERROR: Unknown operation");
		if (findIn(output_commands_, command) != -1) 
			std::cout << std::endl;
	}

private:
	bool keepRunning_;
	CardGame* game_;
	Deck initialDeck_;
	std::unordered_map<std::string, std::function<void(CardGame*)>> game_commands_;
	std::unordered_map<std::string, std::function<void()>> engine_commands_;
	std::unordered_set<std::string> output_commands_;
	void setEngineCommands() {
		engine_commands_["quit"] = std::bind(&CardGameEngine::stop, this);
	}
	template <class G>
	class Operation {
		void (G::*function_)();

	public:
		Operation(void (G::*function)()) : function_(function) {}
		void operator()(CardGame* game) const {
			G* game_pointer = dynamic_cast<G*>(game);
			if (!game_pointer)
				throw CardGameError("ERROR: This game does not support this command!");
			(game_pointer->*function_)();
		}
	};
};

class War;
class Belote;
class Santase;

// This is an example that shows how easy it is to add a new game: 
class NewGame : public CardGame {								   
public:															   
	NewGame(const Deck& deck)									   
		: CardGame(deck,      // Custom game parameters:
			"fancy game",     // Name,								   
			1,                // deck size,									   
			0,                // hand size,									   
			{ "X", "Y", "Z" },// ranks order,					   
			{ "A", "B", "C" } // suits order,					   
		) {}													   
																   
	void new_operation()      // New operations						   
	{															   
		std::cout << "hello";									   
	}															   
																   
	void deal() override      // Override common commands			   
	{															   
		static int deal_counter = 1;							   
		deck_.deal(deal_counter++);								   
	}															   
};																   

int main() {
	CardGameEngine eng;
	eng.addGame<NewGame>("startnew");                  // Just add the game and pass a string that will be the command to start the game
	eng.addCommand("newcmd", &NewGame::new_operation); // And add a command with a function to call when the string is entered

	eng.loadDefaultCommands();

	eng.addGame<War>("War");
	eng.addGame<Belote>("Belote");
	eng.addGame<Santase>("Santase");

	eng.run();
}

class War : public CardGame {
public:
	War(const Deck& deck)
		: CardGame(deck, 
			"War",
			52, 
			26, 
			{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" }
		) {}
};

class Belote : public CardGame {
public:
	Belote(const Deck& deck)
		: CardGame(deck, 
			"Belote",
			32, 
			8,
			{ "7", "8", "9", "J", "Q", "K", "K", "10", "A" }
		) {}
};

class Santase : public CardGame {
public:
	Santase(const Deck& deck)
		: CardGame(deck, 
			"Santase",
			24, 
			6, 
			{ "9", "J", "Q", "K", "10", "A" }
		) {}
};