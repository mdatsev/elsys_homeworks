package org.elsys.cardgame.api;

import java.util.List;

public interface Deck {

	List<Card> getCards();

	Deck setCards(List<Card> cards);
	
	int size();

	int handSize();

	Card drawTopCard();

	Card topCard();

	Card drawBottomCard();

	Card bottomCard();

	Hand deal();

	void sort();
	
	void shuffle();

}
