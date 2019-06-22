package org.elsys.edu;

import java.util.Scanner;

public class MainClass {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String line;
		University uni = new University("Уни", 2);
		while(!(line = sc.nextLine()).equals("END"))
		{
			String[] params = line.split(", ");
			int course = Integer.parseInt(params[1]);
			double avgGrade = Double.parseDouble(params[2]);
			Student student = new Student(params[0], course, avgGrade);
			student.addUncompletedSubject(new Subject("Subject", course % 2 == 0));	
			try {
				uni.signUpForNextYear(student);
			}
			catch(EducationalInstitutionException e)
			{
				System.out.println("Can't sign up this person!");
			}
		}
	}
}
