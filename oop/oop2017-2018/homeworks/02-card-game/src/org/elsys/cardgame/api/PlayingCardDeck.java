package org.elsys.cardgame.api;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

import static org.elsys.cardgame.api.Suit.*;
public class PlayingCardDeck implements Deck {

	private int hand_size;
	private LinkedList<Card> cards = new LinkedList<>();
	private List<Rank> ranks = new ArrayList<>();
	private List<Suit> suits = new ArrayList<>(Arrays.asList(CLUBS, DIAMONDS, HEARTS, SPADES));
	public PlayingCardDeck(int size, int hand_size, List<Rank> ranks){
		this.ranks = ranks;
		this.hand_size = hand_size;
		for(int i = 0; i < ranks.size(); i++)
		{
			for(int j = 0; j < suits.size(); j++)
			{
				cards.add(new PlayingCard(suits.get(j), ranks.get(i)));
			}
		}
	}
	
	public List<Card> getCards() {
		return cards;
	}

	public int size() {
		return cards.size();
	}

	public int handSize() {
		return hand_size;
	}

	public Card drawTopCard() {
		return cards.remove(0);
	}

	public Card topCard() {
		// TODO Auto-generated method stub
		return cards.get(0);
	}

	public Card drawBottomCard() {
		return cards.remove(cards.size()-1);
	}

	public Card bottomCard() {
		return cards.get(cards.size()-1);
	}

	public Hand deal() {
		List<Card> ret = new LinkedList<Card>();
		for(int i = 0; i < hand_size; i++)
			ret.add(cards.remove(0));
		return new PlayingCardHand(ret);
	}

	public void sort() {
		Collections.sort(cards, new Comparator<Card>() {
		    @Override
		    public int compare(Card lhs, Card rhs) {
		    	int ord = ranks.indexOf(lhs.getRank()) - ranks.indexOf(rhs.getRank());
		        return ord != 0 
		        		? ord
		        		: suits.indexOf(lhs.getSuit()) - suits.indexOf(rhs.getSuit());
		    }
		});
	}

	public void shuffle() {
		Collections.shuffle(cards);
	}

}
