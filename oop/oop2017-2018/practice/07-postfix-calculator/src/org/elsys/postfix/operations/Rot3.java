package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Rot3 extends AbstractOperation implements Operation {

	public Rot3(Calculator calculator) {
		super(calculator, "rot3");
	}

	@Override
	public void calculate() {
		Calculator calc = getCalculator();
		double a = calc.popValue();
		double b = calc.popValue();
		double c = calc.popValue();
		calc.addValue(a);
		calc.addValue(c);	
		calc.addValue(b);
	}

}
