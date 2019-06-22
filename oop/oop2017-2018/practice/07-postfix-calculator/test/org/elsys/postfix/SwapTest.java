package org.elsys.postfix;

import org.junit.Test;

public class SwapTest extends CalculatorAbstractTest {

	@Test
	public void test() {
		input("10");
		input("50");
		input("swap");
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(10);
		assertCalculatorStackSize(2);
	}

	@Test
	public void testSwapAndMinus() {
		input("10");
		input("50");
		input("swap");
		input("-");
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(50 - 10);
		assertCalculatorStackSize(1);
	}
}
