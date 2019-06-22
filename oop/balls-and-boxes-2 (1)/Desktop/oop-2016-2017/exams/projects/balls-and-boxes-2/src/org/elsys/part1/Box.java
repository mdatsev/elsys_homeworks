package org.elsys.part1;

import java.util.Iterator;
import java.util.Comparator;
import java.util.Collections;

public class Box extends BallContainer{

	double capacity;

	public Box(double capacity) {
		this.capacity = capacity;
	}

	public boolean add(Ball ball){
		if(this.getVolume() + ball.getVolume() > capacity)
			throw new org.elsys.part1.NotEnoughCapacityException();

		return super.add(ball);
	}

	public Iterator<Ball> getBallsFromSmallest() {
		Collections.sort(balls, new Comparator<Ball>(){
			public int compare(Ball ball, Ball ball2){
				return Double.compare(ball.getVolume(), ball2.getVolume());
			}
		});
		return balls.iterator();
	}

}