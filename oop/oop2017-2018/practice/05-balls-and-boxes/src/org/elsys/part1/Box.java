package org.elsys.part1;

import java.util.Comparator;
import java.util.Iterator;

public class Box extends BallContainer {

	private double capacity;
	
	public Box(double capacity) {
		this.capacity = capacity;
	}

	@Override
	public boolean add(Ball b)
	{
		if(b == null) return false;
		if(total_volume + b.getVolume() > capacity) return false;
		return super.add(b);
	}
	
	public Iterator<Ball> getBallsFromSmallest() {
		balls.sort(new Comparator<Ball>(){
			public int compare( Ball lhs, Ball rhs)
			{
				return Double.compare(lhs.getVolume(), rhs.getVolume());
			}
		});
		return balls.iterator();
	}

}