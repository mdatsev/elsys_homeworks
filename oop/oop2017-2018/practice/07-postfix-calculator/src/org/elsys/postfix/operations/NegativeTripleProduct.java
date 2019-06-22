package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class NegativeTripleProduct extends AbstractOperation implements Operation {

	public NegativeTripleProduct(Calculator calculator) {
		super(calculator, "\\*-\\*");
	}

	@Override
	public void calculate() {
		Calculator calc = getCalculator();
		double a = calc.popValue();
		double b = calc.popValue();
		double c = calc.popValue();
		calc.addValue(- a * b * c);
	}

}
