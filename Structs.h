#pragma once

#ifndef STUDENT_MANAGEMENT_STRUCT_DEFINE

#define STUDENT_MANAGEMENT_STRUCT_DEFINE

// the class struct
typedef struct Class {
	String name;
	float score;
}*ClassList;

// the student struct
typedef struct Student {
	int id;
	String name;
	char sex;
	ClassList classes;
	String address;
}*StudentSet;

// the student node
typedef struct StudentNode {
	StudentNode* head;
	Student data;
	StudentNode* next;
}*StudentList;


#endif

#ifndef STUDENT_STRUCT_FUNCTION

#define STUDENT_STRUCT_FUNCTION

// the declarations about student struct

/**
 * \brief count the student number and return
 * \param studentList the student list
 * \return the number of student list
 */
int StudentCount(StudentList studentList);

/**
 * \brief write the student list data to binary object
 * \param studentList the student list
 * \return write status
 */
Status WriteStudent(StudentList studentList);

/**
 * \brief read the student list data from binary object
 * \return student list
 */
StudentList ReadStudent();

/**
 * \brief set a score by student's id and class name
 * \param studentId student id
 * \param className the name of the class
 * \param score the score
 */
void SetClassScore(int studentId, String className, float score);

/**
 * \brief get someone score by the student's id and the class name
 * \param studentId student id
 * \param className the name of the class
 * \return the score
 */
float GetClassScore(int studentId, String className);

/**
 * \brief insert a student into the student list
 * \param student a new student
 * \param studentList the student list
 */
void AddStudentToList(StudentNode * student, StudentList studentList);

/**
 * \brief find a student in the student list by id
 * \param id student id
 * \param studentList the student list
 * \return a student ptr to the student u want
 */
Student* GetStudent(int id, StudentList studentList);
#endif // !STUDENT_STRUCT_FUNCTION
