package org.elsys.edu;

import java.util.Collection;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public abstract class AbstractEducationalInstitution implements EducationalInstitution {

	Set<Student> students = new HashSet<Student>();
	private String name;
	
	public AbstractEducationalInstitution(String name) {
		this.name = name;
	}
	
	@Override
	public String getName() {
		return name;
	}

	@Override
	public abstract boolean signUpForNextYear(Student student);

	@Override
	public boolean signOut(Student student) {
		return students.remove(student);
	}

	@Override
	public Collection<Student> getStudents() {
		return students;
	}

	@Override
	public List<Student> getStudentsInCourse(int course, boolean orderedByAverageGrade) {
		Stream<Student> result = students.stream()
				.filter(s -> s.getCourse().intValue() == course);
		if(orderedByAverageGrade)
			result = result.sorted((a, b) -> Double.compare(a.getAverageGrade(), b.getAverageGrade()));
		return result.collect(Collectors.toList());
	}

	@Override
	public List<Student> order(Comparator<Student> comparator) {
		return students.stream()
				.sorted(comparator)
				.collect(Collectors.toList());
	}

	@Override
	public Collection<Student> filter(Predicate<Student> predicate) {
		return students.stream()
					.filter(predicate)
					.collect(Collectors.toList());
	}

	@Override
	public Map<Integer, List<Student>> groupStudentsByGrade() {
		return students.stream().collect(Collectors.groupingBy(s -> new Integer((int)Math.round(s.getAverageGrade()))));
	}

}
