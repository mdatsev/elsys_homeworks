package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Constant implements Operation {

	private Calculator calculator;

	private Double value;

	public Constant(Calculator calculator, Double value) {
		this.calculator = calculator;
		this.value = value;
	}
	
	public void calculate() {
		calculator.addValue(value);
	}
	
	public Calculator getCalculator() {
		return calculator;
	}
	
	public String getToken() {
		return value.toString();
	}

}
