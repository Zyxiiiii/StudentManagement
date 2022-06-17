#pragma once
#include"AllHeader.h"

#ifndef STUDENT_MANAGEMENT_STRUCT_DEFINE

#define STUDENT_MANAGEMENT_STRUCT_DEFINE

typedef struct Student {
	int stuNum;
	string name;
	string clazz;
	char sex;
	float score[10];
	string addr;
};

typedef struct StudentNode {
	Student data;
	StudentNode* prior;
	StudentNode* next;
}*StudentList;


#endif

#ifndef STUDENT_STRUCT_FUNCTION

#define STUDENT_STRUCT_FUNCTION

// ѧ���ṹ��������

/// <summary>
/// ��������ѧ������ִ�к���
/// </summary>
/// <param name="studentList">�������ѧ������</param>
/// <param name="func">Ҫ��ÿһ��ѧ��ִ�еĺ���</param>
void stu_foreach(StudentList studentList, bool(*func)(Student*));

/// <summary>
/// ͳ��ѧ������ĳ���
/// </summary>
/// <param name="studentList">ѧ������</param>
/// <returns>����ѧ������ĳ���</returns>
int stu_count(StudentList studentList);

/// <summary>
/// ѧ�������������ƶ�
/// </summary>
/// <param name="studentList">ѧ������</param>
void nextNode(StudentList* studentList);

/// <summary>
/// ѧ�������������ƶ�
/// </summary>
/// <param name="studentList">ѧ������</param>
void lastNode(StudentList* studentList);

#endif // !STUDENT_STRUCT_FUNCTION
