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

// ��ȡ�γ̳ɼ�
float GetClassScore(int studentId, String className);

// ��ѧ����ӵ�������
void AddStudentToList(Student student, StudentList studentList);

// ����ѧ�Ż�ȡѧ��
Student* GetStudent(int id, StudentList studentList);
#endif // !STUDENT_STRUCT_FUNCTION
