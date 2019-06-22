package org.elsys.todo.impl;
import java.util.function.Predicate;

import org.elsys.todo.Criteria;
import org.elsys.todo.Priority;
import org.elsys.todo.Status;
import org.elsys.todo.Task;

public class CriteriaImpl implements Criteria{

	Predicate<Task> predicate;
	
	public CriteriaImpl(Predicate<Task> predicate) {
		this.predicate = predicate;
	}
	
	public CriteriaImpl(Status status) {
		predicate = t -> t.getStatus() == status;
	}

	public CriteriaImpl(Priority priority) {
		predicate = t -> t.getPriority() == priority;
	}

	public CriteriaImpl(String[] tags) {
		predicate = t -> TaskImpl.tagsEqual(t.getTags(), tags);
	}

	@Override
	public Criteria and(Criteria other) {
		return new CriteriaImpl(predicate.and(((CriteriaImpl)other).getPredicate()));
	}

	@Override
	public Criteria or(Criteria other) {
		return new CriteriaImpl(predicate.or(((CriteriaImpl)other).getPredicate()));
	}

	@Override
	public Criteria not() {
		return new CriteriaImpl(predicate.negate());
	}

	public Predicate<Task> getPredicate() {
		return predicate;
	}

}
