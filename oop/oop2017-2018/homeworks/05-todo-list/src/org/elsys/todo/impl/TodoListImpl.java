package org.elsys.todo.impl;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import org.elsys.todo.Criteria;
import org.elsys.todo.Priority;
import org.elsys.todo.Status;
import org.elsys.todo.Task;
import org.elsys.todo.TodoList;

public class TodoListImpl implements TodoList {

	private List<Task> tasks = new ArrayList<>();
	
	public TodoListImpl(Collection<? extends Task> tasks)
	{
		this.tasks = new ArrayList<>(tasks);
	}
	
	public TodoListImpl(String input) {
		tasks = Arrays.stream(input.split("\n"))
					  .map(task -> {
						  	String[] params = task.split("\\|");
						  	return new TaskImpl(
				   /* Status */ Status.valueOf(params[0].trim()),
			  /* Description */ params[1].trim(),
				 /* Priority */ Priority.valueOf(params[2]
											.toUpperCase()
											.trim()),
				     /* Tags */ Arrays.stream(params[3]
										.split(","))
									  .map(tag -> tag.trim())
									  .toArray(String[]::new));
				})
				.collect(Collectors.toList());
	}
	
	@Override
	public Boolean isCompleted() {
		return tasks.stream().allMatch(t -> t.getStatus() == Status.DONE);
	}

	@Override
	public Double percentageCompleted() {
		return (double)tasks.stream()
				.filter(t -> t.getStatus() == Status.DONE).count() / tasks.size() * 100;
	}

	@Override
	public List<Task> getTasks() {
		return tasks;
	}

	@Override
	public TodoList filter(Criteria criteria) {
		return new TodoListImpl(tasks.stream()
									.filter(((CriteriaImpl)criteria).getPredicate())
									.collect(Collectors.toList()));
	}

	@Override
	public TodoList join(TodoList other) {
		return new TodoListImpl(Stream.concat(
										tasks.stream(), 
										other.getTasks().stream())
									.distinct()
									.collect(Collectors.toList()));
	}

}
