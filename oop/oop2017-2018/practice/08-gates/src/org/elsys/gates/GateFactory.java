package org.elsys.gates;

public abstract class GateFactory {

	public static Gate makeXorGate(Wire in1, Wire in2, Wire out, String name) {
		CompositeGate xorGate = new CompositeGate(name);

		xorGate.addInput(in1);
		xorGate.addInput(in2);
		xorGate.addOutput(out);

		Wire a = new Wire("xorA");
		Wire b = new Wire("xorB");
		Wire c = new Wire("xorC");

		Gate orGate = new OrGate(in1, in2, a);
		Gate andGate1 = new AndGate(in1, in2, b);
		Gate notGate = new InverterGate(b, c);
		Gate andGate2 = new AndGate(a, c, out);

		xorGate.addGate(orGate);
		xorGate.addGate(andGate1);
		xorGate.addGate(notGate);
		xorGate.addGate(andGate2);

		return xorGate;
	}

	public static Gate makeXorGate(Wire in1, Wire in2, Wire out) {
		return makeXorGate(in1, in2, out, "XorGate");
	}

	public static Gate makeHalfAdder(Wire a, Wire b, Wire s, Wire c, String name) {
		CompositeGate g = new CompositeGate(name);
		g.addGate(new XorGate(a,b,s));
		g.addGate(new AndGate(a,b,c));
		g.act();
		return g;
	}

	public static Gate makeHalfAdder(Wire a, Wire b, Wire s, Wire c) {
		return makeHalfAdder(a, b, s, c, "HalfAdder");
	}

	public static Gate makeFullAdder(Wire a, Wire b, Wire cIn, Wire sum, Wire cOut, String name) {
		CompositeGate g = new CompositeGate(name);
		Wire ha1ToHa2 = new Wire(name + "HalfAdder1ToHalfAdder2");
		Wire ha1ToOr = new Wire(name + "HalfAdder1ToOr");
		Wire ha2ToOr = new Wire(name + "HalfAdder2ToOr");
		g.addGate(makeHalfAdder(a, b, ha1ToHa2, ha1ToOr));
		g.addGate(makeHalfAdder(cIn, ha1ToHa2, sum, ha2ToOr));
		g.addGate(new OrGate(ha1ToOr, ha2ToOr, cOut));
		g.act();
		return g;
	}

	public static Gate makeFullAdder(Wire a, Wire b, Wire cIn, Wire sum, Wire cOut) {
		return makeFullAdder(a, b, cIn, sum, cOut, "FullAdder");
	}
	
	public static Gate makeRippleCarryAdder(Wire a[], Wire b[], Wire cIn, Wire sum[], Wire cOut) {
		assert a.length == b.length;
		assert a.length == sum.length;
		int count = a.length;
		CompositeGate g = new CompositeGate("RippleCarryAdder");
		Wire lastCarry = cIn;
		for(int i = 0; i < count; i++)
		{
			Wire carryWire = i == count - 1 ? cOut : new Wire("RippleCarry" + i);
			g.addGate(makeFullAdder(a[i], b[i], lastCarry, sum[i], carryWire));
			lastCarry = carryWire;
		}
		g.act();
		return g;
	}
}
