package org.elsys.cardgame.factory;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import org.elsys.cardgame.api.Card;
import org.elsys.cardgame.api.CardException;
import org.elsys.cardgame.api.CardGame;
import org.elsys.cardgame.api.Deck;
import org.elsys.cardgame.api.Game;

public class GameFactory {	
	private static Game addDefaultCardOps(CardGame game)
	{
		return game.addOperation(         "size", (Deck d) -> d.size())
				.addOperation(   "draw_top_card", (Deck d) -> d.drawTopCard())
				.addOperation("draw_bottom_card", (Deck d) -> d.drawBottomCard())
				.addOperation(        "top_card", (Deck d) -> d.topCard())
				.addOperation(     "bottom_card", (Deck d) -> d.drawTopCard())
				.addOperation(         "shuffle", (Deck d) -> d.shuffle())
				.addOperation(            "sort", (Deck d) -> d.sort())
				.addOperation(            "deal", (Game g) -> g.setDealtHand(g.getDeck().deal()));
	}
	
	public static Game getGame(List<? extends Card> from, Deck deck, String gameName)
	{
		List<Card> cardsCopy = new ArrayList<Card>(from),
				correct = deck.getCards();
		if(!cardsCopy.containsAll(correct))
			throw new CardException("Not enough cards for " + gameName);
		return addDefaultCardOps(new CardGame(deck
				.setCards(cardsCopy.stream()
						.distinct()
						.filter(c -> correct.contains(c))
						.collect(Collectors.toList()))));
	}
	
	public static Game createWarGame(List<? extends Card> cards) {
		return getGame(cards, DeckFactory.defaultWarDeck(), "War");
	}

	public static Game createSantaseGame(List<? extends Card> cards) {
		return getGame(cards, DeckFactory.defaultSantaseDeck(), "Santase");
	}

	public static Game createBeloteGame(List<? extends Card> cards) {
		return getGame(cards, DeckFactory.defaultBeloteDeck(), "Belote");
	}
}
