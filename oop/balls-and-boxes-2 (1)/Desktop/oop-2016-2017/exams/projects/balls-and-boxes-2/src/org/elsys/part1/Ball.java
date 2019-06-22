package org.elsys.part1;

public class Ball {
	double volume;
	Color ballColor;

	public Ball(double volume, Color color) {
		this.volume = volume;
		this.ballColor = color;
	}

	public Ball(double volume) {
		this.ballColor = Color.WHITE;
		this.volume = volume;
	}

	public double getVolume() {

		return volume;
	}

	public Color getColor()	 {
		return ballColor;
	}

	public void setBallColor(Color ballColor) {
		this.ballColor = ballColor;
	}

	public void setVolume(double volume) {
		this.volume = volume;
	}
	@Override
	public boolean equals(Object ball){
		if (ball == this) {
			return true;
		}


		if (!(ball instanceof Ball)) {
			return false;
		}

		Ball c = (Ball) ball;


		return Double.compare(this.getVolume(), c.getVolume()) == 0
				&& this.getColor() == c.getColor();
	}

	@Override
	public int hashCode() {
		int result = 17;
		result = 31 * result + (int)this.getVolume();
		result = 31 * result + this.getColor().hashCode();
		return result;
	}
}
