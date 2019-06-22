package org.elsys.cardgame.api;

import java.util.List;

public class PlayingCardHand implements Hand {

	private List<Card> cards;

	public PlayingCardHand(List<Card> cards) {
		this.cards = cards;
	}

	public List<Card> getCards() {
		return cards;
	}

	public int size() {
		return cards.size();
	}

}
