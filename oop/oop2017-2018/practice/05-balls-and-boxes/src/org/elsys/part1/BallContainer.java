package org.elsys.part1;

import java.util.ArrayList;
import java.util.List;

public class BallContainer {

	protected List<Ball> balls;
	protected double total_volume;
	
	public BallContainer() {
		balls = new ArrayList<Ball>();
	}

	/** 
	 * Adds a ball to the container.
	 * @param b the Ball to be added
	 * @return true if b was successfully added
	 */
	public boolean add(Ball b) {
		if(b == null) return false;
		balls.add(b);
		total_volume += b.getVolume();
		return true;
	}

	/**
	 * Removes a ball from the container.
	 * @param b the Ball to be removed
	 * @return true if b was present in the collection
	 */
	public boolean remove(Ball b) {
		if(b == null) return false;
		balls.remove(b);
		return true;
	}

	/**
	 * Returns the sum of the volumes of all balls in the container.
	 * @return
	 */
	public double getVolume() {
		return total_volume;
	}

	/**
	 * Returns the total count of balls in the container.
	 * @return
	 */
	public int size() {
		return balls.size();
	}

	/**
	 *  Removes all balls from the container.
	 */
	public void clear() {
		balls.clear();
	}

	/**
	 * Checks whether a Ball is present in the container.
	 * @param b the Ball to check
	 * @return true if b is present
	 */
	public boolean contains(Ball b) {
		
		return balls.contains(b);
	}

}