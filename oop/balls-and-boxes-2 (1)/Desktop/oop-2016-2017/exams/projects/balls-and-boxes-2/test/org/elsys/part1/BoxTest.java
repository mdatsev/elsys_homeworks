package org.elsys.part1;

import static org.junit.Assert.*;

import java.util.Arrays;
import java.util.Iterator;

import org.elsys.part1.Ball;
import org.elsys.part1.Box;
import org.junit.Test;

public class BoxTest {

	@Test
	public void testMaxCapacity() {
		Box box = new Box(10);
		assertTrue(box.add(new Ball(5)));
		assertTrue(box.add(new Ball(5)));
	}
	
	@Test(expected = NotEnoughCapacityException.class)
	public void testMaxCapacityWhenOver() {
		Box box = new Box(10);
		assertTrue(box.add(new Ball(5)));
		box.add(new Ball(6));
	}

	@Test(expected = NotEnoughCapacityException.class)
	public void testMaxCapacityWithAddAll() {
		Box box = new Box(10);
		box.addAll(Arrays.asList(new Ball(1), new Ball(10)));
	}

	@Test
	public void testNull() {
		Box box = new Box(10);
		assertFalse(box.add(null));
	}

	@Test
	public void testIterator() {
		Box box = new Box(10);
		box.add(new Ball(3));
		box.add(new Ball(2));
		box.add(new Ball(1));

		Iterator<Ball> iter = box.getBallsFromSmallest();
		assertEquals(1, iter.next().getVolume(), 0.01);
		assertEquals(2, iter.next().getVolume(), 0.01);
		assertEquals(3, iter.next().getVolume(), 0.01);
		assertFalse(iter.hasNext());
	}
}
