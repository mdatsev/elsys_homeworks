package org.elsys.gates;

public abstract class NandFactory {

	public static Gate makeNotGate(Wire in, Wire out, String name) {
		return new NandGate(in,in,out,name);
	}

	public static Gate makeNotGate(Wire in, Wire out) {
		return makeNotGate(in, out, "NandNot");
	}

	public static Gate makeAndGate(Wire in1, Wire in2, Wire out, String name) {
		CompositeGate g = new CompositeGate(name);
		Wire w = new Wire(name + "A");
		g.addGate(new NandGate(in1, in2, w));
		g.addGate(makeNotGate(w, out));
		g.act();
		return g;
	}

	public static Gate makeAndGate(Wire in1, Wire in2, Wire out) {
		return makeAndGate(in1, in2, out, "NandAnd");
	}

	public static Gate makeOrGate(Wire in1, Wire in2, Wire out, String name) {
		CompositeGate g = new CompositeGate(name);
		Wire w1 = new Wire(name + "A");
		Wire w2 = new Wire(name + "B");
		g.addGate(makeNotGate(in1, w1));
		g.addGate(makeNotGate(in2, w2));
		g.addGate(new NandGate(w1, w2, out));
		g.act();
		return g;
	}

	public static Gate makeOrGate(Wire in1, Wire in2, Wire out) {
		return makeOrGate(in1, in2, out, "NandOr");
	}

	public static Gate makeXorGate(Wire in1, Wire in2, Wire out, String name) {
		CompositeGate g = new CompositeGate(name);
		
		Wire wsplit = new Wire(name + "SplitWire");
		Wire w1 = new Wire(name + "A");
		Wire w2 = new Wire(name + "B");
		
		g.addGate(new NandGate(in1, in2, wsplit));
		g.addGate(new NandGate(in1, wsplit, w1));
		g.addGate(new NandGate(in2, wsplit, w2));
		g.addGate(new NandGate(w1, w2, out));
		
		g.act();
		
		return g;
	}

	public static Gate makeXorGate(Wire in1, Wire in2, Wire out) {
		return makeXorGate(in1, in2, out, "NandXor");
	}

}
