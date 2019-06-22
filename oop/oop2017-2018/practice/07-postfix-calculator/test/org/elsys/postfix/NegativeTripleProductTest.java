package org.elsys.postfix;

import java.util.EmptyStackException;

import org.junit.Test;

public class NegativeTripleProductTest extends CalculatorAbstractTest {

	@Test(expected = EmptyStackException.class)
	public void testWithNotEnoughValuesInStack() {
		input("1");
		input("2");
		input("\\*-\\*");
		inputCtrlC();
		runCalculator();
	}

	@Test
	public void test() {
		input("1");
		input("2");
		input("3");
		input("\\*-\\*");
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(- 1 * 2 * 3);
		assertCalculatorStackSize(1);
	}
}
