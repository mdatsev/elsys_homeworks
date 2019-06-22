package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Division extends BinaryOperation implements Operation {

	public Division(Calculator calculator) {
		super(calculator, "/");
	}

	@Override
	protected double doCalculate(double a, double b) {
		return b / a;
	}

}
