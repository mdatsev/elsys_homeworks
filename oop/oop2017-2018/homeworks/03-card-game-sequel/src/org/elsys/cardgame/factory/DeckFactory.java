package org.elsys.cardgame.factory;

import java.util.Arrays;

import org.elsys.cardgame.api.Deck;
import org.elsys.cardgame.api.PlayingCardDeck;
import org.elsys.cardgame.api.Rank;
import static org.elsys.cardgame.api.Rank.*;

public class DeckFactory {

	public static Deck defaultWarDeck() {
		return new PlayingCardDeck(52, 26, Arrays.asList(Rank.values()));
	}

	public static Deck defaultBeloteDeck() {
		return new PlayingCardDeck(32, 8, Arrays.asList(SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE ));
	}
	
	public static Deck defaultSantaseDeck() {
		return new PlayingCardDeck(24, 6, Arrays.asList(NINE, JACK, QUEEN, KING, TEN, ACE));
	}
}
