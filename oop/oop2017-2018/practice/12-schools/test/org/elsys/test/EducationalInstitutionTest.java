package org.elsys.test;

import static org.junit.jupiter.api.Assertions.*;

import org.elsys.edu.HighSchool;
import org.elsys.edu.Student;
import org.elsys.edu.University;
import org.junit.Before;
import org.junit.jupiter.api.Test;

class EducationalInstitutionTest {

	University uni;
	HighSchool sch;
	
	@Before
	void setup() {
		uni = new University("Uni", 2);
		sch = new HighSchool("SOU");
		//uni.signUpForNextYear(new Student("Pesho", 1));
		uni.signUpForNextYear(new Student("Gosho"));
	}

	
	@Test
	void getStudentsInCourseSchool() {
		//uni.getStudentsInCourse(1, orderedByAverageGrade)
	}
	
	@Test
	void getStudentsInCourseUniversity() {
		
	}

}
