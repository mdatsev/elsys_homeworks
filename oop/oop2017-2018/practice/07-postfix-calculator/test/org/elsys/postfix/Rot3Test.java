package org.elsys.postfix;

import org.junit.Test;

public class Rot3Test extends CalculatorAbstractTest {

	@Test
	public void test() {
		input("1");
		input("2");
		input("3");
		input("rot3"); // 3 1 2
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(2);
		assertCalculatorStackSize(3);
	}

	@Test
	public void testSwapAndMinus() {
		input("1");
		input("2");
		input("3"); 
		input("rot3");
		input("-");
		input("+");
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(2); // 3 1 2 - + = 2
		assertCalculatorStackSize(1);
	}
}
