#pragma once

#ifndef STUDENT_MANAGEMENT_STRUCT_DEFINE

#define STUDENT_MANAGEMENT_STRUCT_DEFINE

// the class struct
typedef struct Lesson {
	String name;
	float score;
}*LessonList;

// the student struct
typedef struct Student {
	int id;
	String name;
	char sex;
	LessonList lessons;
	String address;
}*StudentSet;

// the student node
typedef struct StudentNode {
	StudentNode* head;
	Student data;
	StudentNode* next;
}*StudentList;

static StudentList student_list;


#endif

#ifndef STUDENT_STRUCT_FUNCTION

#define STUDENT_STRUCT_FUNCTION

// the declarations about student struct

/**
 * \brief count the student number and return
 * \param student_list the student list
 * \return the number of student list
 */
int StudentCount(StudentList student_list);

/**
 * \brief write the student list data to binary object
 * \param student_list the student list
 * \return write status
 */
Status WriteStudent(StudentList student_list);

/**
 * \brief read the student list data from binary object
 * \return student list
 */
StudentList ReadStudent();

/**
 * \brief set a score by student's id and lesson name
 * \param student_id student id
 * \param lesson_name the name of the lesson
 * \param score the score
 */
void SetLessonScore(int student_id, String lesson_name, float score);

/**
 * \brief get someone score by the student's id and the lesson name
 * \param student_id student id
 * \param lesson_name the name of the lesson
 * \return the score
 */
float GetLessonScore(int student_id, String lesson_name);

/**
 * \brief insert a student into the student list
 * \param student a new student
 * \param student_list the student list
 */
void AddStudentToList(StudentNode * student, StudentList student_list);

/**
 * \brief find a student in the student list by id
 * \param id student id
 * \param student_list the student list
 * \return a student ptr to the student u want
 */
Student* GetStudent(int id, StudentList student_list);
#endif // !STUDENT_STRUCT_FUNCTION
