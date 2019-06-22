package org.elsys.postfix;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.EmptyStackException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

import org.elsys.postfix.operations.CompositeOperation;
import org.elsys.postfix.operations.Constant;
import org.elsys.postfix.operations.Cos;
import org.elsys.postfix.operations.Division;
import org.elsys.postfix.operations.Duplicate;
import org.elsys.postfix.operations.Minus;
import org.elsys.postfix.operations.Multiplication;
import org.elsys.postfix.operations.Negate;
import org.elsys.postfix.operations.NegativeTripleProduct;
import org.elsys.postfix.operations.Operation;
import org.elsys.postfix.operations.Plus;
import org.elsys.postfix.operations.Rot3;
import org.elsys.postfix.operations.Sin;
import org.elsys.postfix.operations.Swap;

public class Calculator {

	private Map<String, Operation> operations = new HashMap<>();

	private List<Double> stack = new LinkedList<>();

	private InputStream in;

	private PrintStream out;
	
	public Calculator(InputStream in, PrintStream out) {
		this.in = in;
		this.out = out;
		addOperation(new Negate(this));
		addOperation(new Duplicate(this));
		addOperation(new Minus(this));
		addOperation(new Plus(this));
		addOperation(new Multiplication(this));
		addOperation(new Division(this));
		addOperation(new NegativeTripleProduct(this));
		addOperation(new Sin(this));
		addOperation(new Cos(this));
		addOperation(new Swap(this));
		addOperation(new Rot3(this));
	}

	public void run() {
		String input;
		try (Scanner scanner = new Scanner(in)) {
			boolean inCompositeDef = false;
			CompositeOperation composite = null;
			while (scanner.hasNext()) {
				out.print(stack.size() + ": ");
				input = scanner.next();
				Operation operation = getOperation(input);
				if(inCompositeDef)
				{
					if(operation != null)
						composite.addOperation(operation);
					else if (input.equals("def")) {
						addOperation(composite);
						inCompositeDef = false;
					}
					else if (isDouble(input))
						composite.addOperation(new Constant(this, Double.valueOf(input))); 
					else
						throw new UnsupportedOperationException();
				}
				else
				{
					if(operation != null)
						operation.calculate();
					else if(input.startsWith("\\")) {
						composite = new CompositeOperation(this, input.substring(1));
						inCompositeDef = true;
					}
					else if (isDouble(input))
						stack.add(Double.valueOf(input));
					else
						throw new UnsupportedOperationException();
				}
			}
		}
	}

	private static boolean isDouble(String input) {
		try {
			Double.valueOf(input);
		} catch (NumberFormatException e) {
			return false;
		}
		return true;
	}

	public void addOperation(Operation operation) {
		operations.put(operation.getToken(), operation);
	}

	public Operation getOperation(String token) {
		return operations.get(token);
	}

	public Double popValue() {
		int lastIndex = stack.size() - 1;
		try
		{
			Double value = stack.get(lastIndex);
			stack.remove(lastIndex);
			return value;
		}
		catch(IndexOutOfBoundsException e)
		{
			throw new EmptyStackException();
		}
	}

	Double lastValue() {
		return stack.get(stack.size() - 1);
	}

	public void addValue(double value) {
		out.println(value);
		stack.add(value);
	}

	int stackSize() {
		return stack.size();
	}
}