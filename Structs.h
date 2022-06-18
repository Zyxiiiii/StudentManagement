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

// 学生结构函数声明

// 统计学生数量
int StudentCount(StudentList studentList);

// 写入学生信息
Status WriteStudent(StudentList studentList);

// 读取学生信息
StudentList ReadStudent();

// 设置课程成绩
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
