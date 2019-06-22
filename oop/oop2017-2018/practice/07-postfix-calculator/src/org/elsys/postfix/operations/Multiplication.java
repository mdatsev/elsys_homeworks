package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Multiplication extends BinaryOperation implements Operation {

	public Multiplication(Calculator calculator) {
		super(calculator, "*");
	}

	@Override
	protected double doCalculate(double a, double b) {
		return a * b;
	}

}
