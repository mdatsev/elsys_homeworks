package org.elsys.cardgame.api;

public class PlayingCard implements Card {

	private final Suit suit;
	private final Rank rank;
	
	public PlayingCard(Suit suit, Rank rank){
		this.suit = suit;
		this.rank = rank;
	}
	
	public Suit getSuit()
	{
		return suit;
	}

	public Rank getRank()
	{
		return rank;
	}
	
	public String toString()
	{
		return suit + rank.toString();
	}

	@Override
	public boolean equals(Object obj)
	{
		if(this == obj) return true;
		if(obj instanceof PlayingCard){
			PlayingCard card = (PlayingCard) obj;
			return card != null && rank == card.rank && suit == card.suit;
		}
		return false;
	}

	@Override 
	public int hashCode() {
	    return rank.ordinal() * 100 + suit.ordinal();
	}

}
