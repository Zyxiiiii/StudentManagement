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

// 学生结构函数声明

/// <summary>
/// 对所给的学生链表执行函数
/// </summary>
/// <param name="studentList">待处理的学生链表</param>
/// <param name="func">要对每一个学生执行的函数</param>
void stu_foreach(StudentList studentList, bool(*func)(Student*));

/// <summary>
/// 统计学生链表的长度
/// </summary>
/// <param name="studentList">学生链表</param>
/// <returns>返回学生链表的长度</returns>
int stu_count(StudentList studentList);

/// <summary>
/// 学生链表结点向下移动
/// </summary>
/// <param name="studentList">学生链表</param>
void nextNode(StudentList* studentList);

/// <summary>
/// 学生链表结点向上移动
/// </summary>
/// <param name="studentList">学生链表</param>
void lastNode(StudentList* studentList);

#endif // !STUDENT_STRUCT_FUNCTION
