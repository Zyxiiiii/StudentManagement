#pragma once
#include"AllHeader.h"

#ifndef STUDENT_MANAGEMENT_STRUCT_DEFINE

#define STUDENT_MANAGEMENT_STRUCT_DEFINE

typedef struct Class {
	String name;
	float score;
}*ClassList;


typedef struct Student {
	int id;
	String name;
	char sex;
	ClassList classes;
	String addr;
}*StudentSet;

typedef struct StudentNode {
	StudentNode* head;
	Student data;
	StudentNode* next;
}*StudentList;


#endif

#ifndef STUDENT_STRUCT_FUNCTION

#define STUDENT_STRUCT_FUNCTION

// ѧ���ṹ��������

// ͳ��ѧ������
int StudentCount(StudentList studentList);

// д��ѧ����Ϣ
Status WriteStudent(StudentList studentList);

// ��ȡѧ����Ϣ
StudentList ReadStudent();

// ���ÿγ̳ɼ�
void SetClassScore(int studentId, String className, float score);

/**/
float GetClassScore(int studentId, String className);

/*
	insert a new student into the student list

	@param student: new student
	@param studentList: the student list
*/
void AddStudentToList(Student student, StudentList studentList);

/*
	get student from a student list by id

	@param id: the id of the student which u want
	@param studentList: the student list
*/
Student* GetStudent(int id, StudentList studentList);
#endif // !STUDENT_STRUCT_FUNCTION
