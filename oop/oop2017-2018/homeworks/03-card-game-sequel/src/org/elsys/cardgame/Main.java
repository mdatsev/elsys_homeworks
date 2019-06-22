package org.elsys.cardgame;

import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;


import org.elsys.cardgame.api.CardException;
import org.elsys.cardgame.api.CardGame;
import org.elsys.cardgame.api.Game;
import org.elsys.cardgame.api.PlayingCard;
import org.elsys.cardgame.api.Rank;
import org.elsys.cardgame.api.Suit;
import static org.elsys.cardgame.factory.GameFactory.*;
public class Main {
	
	private static Suit getSuit(String str) {
		return Arrays.stream(Suit.values())
			     .filter(c -> c.getSymbol().equals(str))
			     .findFirst().orElseThrow(() -> new CardException("Invalid card!"));
	}
	// how to make this generic?? java??
	private static Rank getRank(String str) {
		return Arrays.stream(Rank.values())
				.filter(c -> c.getSymbol().equals(str))
	     		.findFirst().orElseThrow(() -> new CardException("Invalid card!"));
	}
	
	public static List<PlayingCard> extractCards(String str)
	{
		return Arrays.stream(str.split(" "))
		.map(card -> new PlayingCard(getSuit(card.substring(0, 1)), 
				getRank(card.substring(1))))
		.collect(Collectors.toList());
	}
	
	public static class GameWrapper { public Game game; }
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		List<PlayingCard> cards = extractCards(sc.nextLine());
		GameWrapper slave = new GameWrapper();
		CardGame hubGame = new CardGame()
				.addOperation(    "War", () -> slave.game = createWarGame(cards))
				.addOperation( "Belote", () -> slave.game = createBeloteGame(cards))
				.addOperation("Santase", () -> slave.game = createSantaseGame(cards))
				.addOperation(   "quit", () -> System.exit(0))
				.addDefaultOperation((String cmd) -> {
					if(slave.game == null)
						throw new CardException("No deck.");
					slave.game.process(cmd);
				});
		while(true)
			try{
				hubGame.process(sc.nextLine());
			}catch(CardException e){
				System.out.println("ERROR: " + e.getMessage());
			}
	}

}
