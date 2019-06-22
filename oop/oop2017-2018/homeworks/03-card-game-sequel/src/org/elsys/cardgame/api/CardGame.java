package org.elsys.cardgame.api;

import java.util.LinkedList;
import java.util.List;
import java.util.Optional;
import java.util.function.Consumer;

public class CardGame implements Game {

	Deck deck;
	Hand hand;
	List<Operation> operations = new LinkedList<Operation>();
	Consumer<String> defaultOperation;
	
	public CardGame() {}
	
	public CardGame(Deck deck)
	{
		this.deck = deck;
	}
	
	@Override
	public Deck getDeck() {
		return deck;
	}

	@Override
	public Hand getDealtHand() {
		return hand;
	}

	@Override
	public void setDealtHand(Hand hand) {
		this.hand = hand;
	}

	@Override
	public void process(String command) {
		Optional<Operation> found = operations.stream()
				.filter(o -> o.getName().equals(command)).findFirst();
		if(!found.isPresent())
		{
			if(defaultOperation != null)
				defaultOperation.accept(command);
			else
				throw new CardException("Unknown operation!");
		}
		else
			found.get().execute();
		
	}

	@Override
	public void addOperation(Operation operation) {
		operations.add(operation);
	}
	
	public CardGame addOperation(String name, GameAction action) {
		operations.add(new GameOperation(name, this, action));
		return this;
	}
	
	public CardGame addOperation(String name, DeckAction action) {
		operations.add(new GameOperation(name, this, action));
		return this;
	}
	
	public CardGame addOperation(String name, VoidGameAction action) {
		operations.add(new GameOperation(name, this, action));
		return this;
	}
	
	public CardGame addOperation(String name, VoidDeckAction action) {
		operations.add(new GameOperation(name, this, action));
		return this;
	}
	
	public CardGame addOperation(String name, Runnable action) {
		operations.add(new GameOperation(name, this, action));
		return this;
	}
	
	public CardGame addDefaultOperation(Consumer<String> action) {
		defaultOperation = action;
		return this;
	}
	
}
