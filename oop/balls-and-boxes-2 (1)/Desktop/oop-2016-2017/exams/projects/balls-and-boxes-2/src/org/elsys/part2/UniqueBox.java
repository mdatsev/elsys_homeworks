package org.elsys.part2;

import org.elsys.part1.Ball;
import org.elsys.part1.Box;

public class UniqueBox extends Box {
    public UniqueBox(double capacity) {
        super(capacity);
    }
    public boolean add(Ball ball){

            if(balls.contains(ball))
                return false;

            return super.add(ball);
    }
}
