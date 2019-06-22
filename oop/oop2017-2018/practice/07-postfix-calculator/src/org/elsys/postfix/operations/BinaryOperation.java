package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public abstract class BinaryOperation extends AbstractOperation {

	public BinaryOperation(Calculator calculator, String token) {
		super(calculator, token);
	}

	@Override
	public void calculate() {
		Calculator calc = getCalculator();
		double a = calc.popValue();
		double b = calc.popValue();
		double result = doCalculate(a, b);
		calc.addValue(result);
	}

	protected abstract double doCalculate(double a, double b);
}
