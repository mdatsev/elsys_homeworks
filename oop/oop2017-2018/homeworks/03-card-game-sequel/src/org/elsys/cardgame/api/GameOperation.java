package org.elsys.cardgame.api;

public class GameOperation implements Operation {

	Game game;
	String name;
	GameAction action;
	
	public GameOperation(String name, Game game, GameAction action) {
		this.game = game;
		this.name = name;
		this.action = action;
	}
	
	public GameOperation(String name, Game game, DeckAction action) {
		this(name, game, (Game g) -> action.action(g.getDeck()));
	}
	
	public GameOperation(String name, Game game, VoidGameAction action) {
		this(name, game, (Game g) -> { action.action(g); return g.getDealtHand(); });
	}
	
	public GameOperation(String name, Game game, VoidDeckAction action) {
		this(name, game, (Game g) -> { action.action(g.getDeck()); return g.getDeck(); });
	}

	public GameOperation(String name, CardGame game, Runnable action) {
		this(name, game, (Game g) -> { action.run(); return null;});
	}

	@Override
	public String getName() {
		return name;
	}
	
	@Override
	public void execute() {
		Object result = action.action(game);
		if(result != null)
			System.out.println(result);
	}

}
