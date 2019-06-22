package org.elsys.gates;

import java.util.Scanner;

public class Program {

	private static void numberToWires(int number, Wire[] wires) {
		for (int i = 0; i < wires.length; ++i) {
			wires[i].setSignal((number & 1 << i) != 0);
		}
	}

	private static int wiresToNumber(Wire[] wires) {
		int result = 0;
		for (int i = 0; i < wires.length; ++i) {
			if(wires[i].getSignal())
				result += 1 << i;
		}
		return result;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Wire[] aWires = new Wire[8], 
				bWires = new Wire[8], 
				sumWires = new Wire[8];
		
		for (int i = 0; i < 8; i++) {
			aWires[i]= new Wire("a" + i);
			bWires[i]= new Wire("b" + i);
			sumWires[i]= new Wire("sum" + i);
		}
		
		Gate adder = GateFactory.makeRippleCarryAdder(aWires, bWires, 
				new Wire("cIn"), sumWires, new Wire("cOut"));
		
		for (;;) {
			int aInput = sc.nextInt();
			int bInput = sc.nextByte();
			numberToWires(aInput, aWires);
			numberToWires(bInput, bWires);
			
			adder.act();
			int sum = wiresToNumber(sumWires);
			System.out.println(sum);
		}
	}
}
