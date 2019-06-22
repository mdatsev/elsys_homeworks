package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Swap extends BinaryOperation implements Operation {

	public Swap(Calculator calculator) {
		super(calculator, "swap");
	}

	@Override
	public double doCalculate(double a, double b) {
		getCalculator().addValue(a);	
		return b;
	}

}
