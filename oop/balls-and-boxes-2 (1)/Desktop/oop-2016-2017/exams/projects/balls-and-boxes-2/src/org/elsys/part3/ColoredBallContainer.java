package org.elsys.part3;

import org.elsys.part1.Ball;
import org.elsys.part1.BallContainer;
import org.elsys.part1.Color;

public class ColoredBallContainer extends BallContainer {

	Color color;

	public ColoredBallContainer(Color color) {
		this.color = color;
	}

	public Color getColor() {
		return color;
	}

	public boolean add(Ball ball){
		if(ball.getColor() == this.color)
			return balls.add(ball);

		return false;
	}

}
