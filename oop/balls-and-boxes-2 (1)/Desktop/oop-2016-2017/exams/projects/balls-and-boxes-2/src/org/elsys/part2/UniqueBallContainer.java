package org.elsys.part2;

import org.elsys.part1.Ball;
import org.elsys.part1.BallContainer;

public class UniqueBallContainer extends BallContainer {
    public boolean add(Ball ball){
        if(balls.contains(ball))
            return false;

        return balls.add(ball);
    }
}
