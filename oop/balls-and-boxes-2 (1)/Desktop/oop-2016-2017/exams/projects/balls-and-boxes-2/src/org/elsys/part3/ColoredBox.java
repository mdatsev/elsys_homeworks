package org.elsys.part3;

import org.elsys.part1.Ball;
import org.elsys.part1.Box;
import org.elsys.part1.Color;

public class ColoredBox extends Box {
    Color color;
    ColoredBox(Color color,double capacity){
        super(capacity);
        this.color = color;
    }

    public Color getColor(){
        return color;
    }

    public boolean add(Ball ball){
        if(ball.getColor() == this.color)
            return super.add(ball);

        return false;
    }
}
