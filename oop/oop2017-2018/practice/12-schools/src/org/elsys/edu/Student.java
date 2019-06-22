package org.elsys.edu;

import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class Student {

	String name;
	Integer course;
	double averageGrade;
	Set<Subject> subjects = new HashSet<Subject>();
	
	public Student(String name) {
		setName(name);
	}	
	
	public Student(String name, int course, double averageGrade) {
		setName(name);
		setCourse(course);
		setAverageGrade(averageGrade);
	}	
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Integer getCourse() {
		return course;
	}

	public void setCourse(Integer course) {
		this.course = course;
	}

	public double getAverageGrade() {
		return averageGrade;
	}

	public void setAverageGrade(double averageGrade) {
		this.averageGrade = averageGrade;
	}

	public List<Subject> getUncompletedSubjects() {
		return subjects.stream().collect(Collectors.toList());
	}

	public boolean addUncompletedSubject(Subject subject) {
		return subjects.add(subject);
	}

	public boolean removeUncompletedSubject(Subject subject) {
		return subjects.remove(subject);
	}
}
