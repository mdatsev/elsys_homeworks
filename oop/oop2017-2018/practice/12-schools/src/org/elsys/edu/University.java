package org.elsys.edu;

import java.util.Collection;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.function.Predicate;

public class University extends AbstractEducationalInstitution {

	private int maxUncompletedSubjects;
	
	public University(String name, int maxUncompletedSubjects) {
		super(name);
		this.maxUncompletedSubjects = maxUncompletedSubjects;
	}

	@Override
	public boolean signUpForNextYear(Student student) {
		if(student.getUncompletedSubjects().size() > maxUncompletedSubjects)
			throw new EducationalInstitutionException();
		if(students.add(student))
		{	
			Integer current = student.getCourse();
			student.setCourse(current != null ? current + 1 : 1);
			return true;
		}
		return false;
	}
}
