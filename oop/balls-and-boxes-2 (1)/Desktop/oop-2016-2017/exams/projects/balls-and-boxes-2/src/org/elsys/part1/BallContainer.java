package org.elsys.part1;

import java.util.Collection;
import java.util.ArrayList;
import java.util.List;

public class BallContainer {

	protected List<Ball> balls;

	public BallContainer() {
		balls = new ArrayList<>();
	}

	/** 
	 * Adds a ball to the container.
	 * @param b the Ball to be added
	 * @return true if b was successfully added
	 */
	public boolean add(Ball b) {
		return balls.add(b);
	}

	/**
	 * Adds all balls to a container.
	 * @param balls
	 * @return true if all balls were added, false otherwise
	 */
	public boolean addAll(Collection<Ball> balls) {
		return balls.addAll(balls);
	}

	/**
	 * Removes a ball from the container.
	 * @param b the Ball to be removed
	 * @return true if b was present in the collection
	 */
	public boolean remove(Ball b) {
		return balls.remove(b);
	}

	/**
	 * Returns the sum of the volumes of all balls in the container.
	 * @return
	 */
	public double getVolume() {
		double sum = 0.0;
		for(Ball ball :balls){
			sum += ball.getVolume();
		}
		return sum;
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