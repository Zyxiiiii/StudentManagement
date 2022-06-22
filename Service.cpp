﻿#include "AllHeader.h"

#define YES 0

#define NO 1

/**
 * \brief ask client to ensure this operation
 * \return a status code
 */
Status EnsuretheOparation();

/**
 * \brief check this input is effect or not
 * \param size the max size
 * \return the effect data
 */
String CheckAndGetInput(int size);

Status EnsuretheOparation()
{
    printf("\t\t\t确认要执行吗？(0:取消本次操作, 1:确定):");
    switch (GetOrderInput())
    {
    case 0:
        return NO;
    case 1:
        return YES;
    default:
        printf("\t\t\t请输入正确的命令!\n");
        EnsuretheOparation();
    }
}

String CheckAndGetInput(int size)
{
    String input = (String)malloc(sizeof(char) * (size + 1));
    scanf_s("%s", input, size + 1);
    if (strcmp(input, "") != 0)
    {
        return input;
    }
    printf("\t\t\t请输入正确的数据:");
    return CheckAndGetInput(size);
}


void AddStudent()
{
    system("CLS");

    // receive the data
    Student student_data = {
        NOT_ID,
        (String)malloc(sizeof(char) * 32),
        '\0',
        CreateNewLessonList(),
        (String)malloc(sizeof(char) * 60)
    };
    StudentNode student = CreateNewStudentNode(student_data);
    printf("\n\n\n\t\t\t请输入该学生的名字(大于一个字，16个字以内):");
    strcpy_s(student.data.name, 16 * 2, CheckAndGetInput(16 * 2));
    printf("\n\t\t\t请输入该学生的性别(男/女):");
    String data_keeper = CheckAndGetInput(3);
    while (strcmp(data_keeper, "男") != 0 && strcmp(data_keeper, "女") != 0)
    {
        printf("\n\t\t\t请输入正确的性别(男/女):");
        data_keeper = CheckAndGetInput(3);
    }
    student.data.sex = strcmp(data_keeper, "男") == 0 ? MAN : WOMEN;
    printf("\n\t\t\t请输入该学生的住址(30字以内):");
    data_keeper = CheckAndGetInput(30 * 2);
    strcpy_s(student.data.address, 30 * 2, data_keeper);

    StudentList student_list = *ReadStudent();

    student.data.id = StudentCount(student_list) + 1;

    AddStudentToList(&student, &student_list);

    // TODO resolve the variable would be override
    if (WriteStudent(&student_list) == OK)
    {
        printf("\n\t\t\t新增学生成功\n\n\t\t\t");
        system("pause");
    }
    else
    {
        printf("\n\t\t\t新增学生失败\n\n\t\t\t");
        system("pause");
    }

    free(student_list);
    student_list = NULL;

    StudentInfoWindow();
}
