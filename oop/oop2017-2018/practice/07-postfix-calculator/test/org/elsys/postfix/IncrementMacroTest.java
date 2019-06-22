package org.elsys.postfix;

import org.junit.Test;

public class IncrementMacroTest extends CalculatorAbstractTest {

	@Test
	public void test() {
		input("\\inc");
		input("1");
		input("+");
		input("def");
		
		input("2");
		input("inc");
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(3);
	}

}
