package org.elsys.part1;

public class Ball {

	private double volume;
	private Color color;
	
	public Ball(double volume, Color color) {
		this.volume = volume;
		this.color = color;
	}

	public Ball(double volume) {
		this.volume = volume;
	}

	public double getVolume() {
		return volume;
	}
	
	public void setVolume(double volume)
	{
		this.volume = volume;
	}
	
	@Override
	public boolean equals(Object rhs)
	{
		return this.volume == ((Ball)rhs).volume && ((Ball)rhs).color == this.color;
	}
	
	public void setColor(Color color)
	{
		this.color = color;
	}

	public Color getColor() {
		return color;
	}
}