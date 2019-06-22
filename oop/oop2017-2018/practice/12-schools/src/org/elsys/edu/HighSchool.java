package org.elsys.edu;

public class HighSchool extends AbstractEducationalInstitution {

	public HighSchool(String name) {
		super(name);
	}

	@Override
	public boolean signUpForNextYear(Student student) {
		if(student.getUncompletedSubjects().isEmpty() && students.add(student))
		{	
			Integer current = student.getCourse();
			student.setCourse(current != null ? current + 1 : 1);
			return true;
		}
		return false;
	}
	
}
