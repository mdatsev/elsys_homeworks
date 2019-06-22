package org.elsys.todo.impl;

import java.util.Arrays;

import org.elsys.todo.Priority;
import org.elsys.todo.Status;
import org.elsys.todo.Task;

public class TaskImpl implements Task {

	public TaskImpl(Status status, String description, Priority priority, String[] tags) {
		this.status = status;
		this.description = description;
		this.priority = priority;
		this.tags = tags;
	}

	public static boolean tagsEqual(String[] tags1, String[] tags2)
	{
		Arrays.sort(tags1);
		Arrays.sort(tags2);
		return tags1.equals(tags2);
	}
	
	private Status status;
	private String description;
	private Priority priority;
	private String[] tags;
	
	@Override
	public Status getStatus() {
		return status;
	}

	@Override
	public String getDescription() {
		return description;
	}

	@Override
	public Priority getPriority() {
		return priority;
	}

	@Override
	public String[] getTags() {
		return tags;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((description == null) ? 0 : description.hashCode());
		result = prime * result + ((priority == null) ? 0 : priority.hashCode());
		result = prime * result + ((status == null) ? 0 : status.hashCode());
		Arrays.sort(tags);
		result = prime * result + Arrays.hashCode(tags);
		return result;
	}

	@Override
	public boolean equals(Object obj) {
	    if (obj == null) {
	        return false;
	    }
	    if (!TaskImpl.class.isAssignableFrom(obj.getClass())) {
	        return false;
	    }
	    final TaskImpl other = (TaskImpl) obj;
	    if (this.status != other.status || 
	    		this.priority != other.priority ||
	    		this.description != other.description ||
	    		!tagsEqual(this.tags, other.tags)) {
	        return false;
	    }
	    return true;
	}

}
