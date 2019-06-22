package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Duplicate extends UnaryOperation implements Operation {

	public Duplicate(Calculator calculator) {
		super(calculator, "dup");
	}

	@Override
	public double doCalculate(double value) {
		getCalculator().addValue(value);	
		return value;
	}

}
