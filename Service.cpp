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
    printf("\n\t\t\t确认要执行吗？(0:取消本次操作, 1:确定):");
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
        (String)malloc(sizeof(char) * 20),
        '\0',
        CreateNewLessonList(),
        (String)malloc(sizeof(char) * 60)
    };
    StudentNode student = CreateNewStudentNode(student_data);
    printf("\n\n\n\t\t\t请输入该学生的名字(大于一个字，16个字以内):");
    strcpy_s(student.data.name, 16 * 2, CheckAndGetInput(16 * 2));
    printf("\n\t\t\t请输入该学生的班别(格式为英文缩写+年级+班号):");
    strcpy_s(student.data.clazz, 20, CheckAndGetInput(20));
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

    student.data.id = GetMaxId(student_list) + 1;

    AddStudentToList(&student, &student_list);

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

void DeleteStudent()
{
    system("CLS");

    printf("\n\n\t\t\t请输入想要删除的学生id(请不要输入非数字的字符, 因为那将视为id的结束符):");
    // check input
    String input_check = CheckAndGetInput(15);
    char id_str[15] = {0};
    for (int i = 0; i < 16; i++)
    {
        if (14 == i)
        {
            id_str[i] = '\0';
            break;
        }
        int num = input_check[i] - '0';
        if (num >= 0 && num <= 9)
        {
            id_str[i] = input_check[i];
        }
        else
        {
            id_str[i] = '\0';
            break;
        }
    }
    int size = strlen(id_str);
    unsigned long long id = 0L;
    for (int i = 0; i < size; i++)
    {
        id += (id_str[i] - '0') * (unsigned long long)pow(10, size - i - 1);
    }

    StudentList* student_list = ReadStudent();

    if (EnsuretheOparation() == YES && RemoveStudent(id, student_list) == OK && WriteStudent(student_list) == OK)
    {
        printf("\n\t\t\t删除学生信息成功!");
        system("pause");
    }
    else
    {
        printf("\n\t\t\t删除学生信息失败!\n\n\t\t\t请检查输入的id是否正确");
        system("pause");
    }

    StudentInfoWindow();
}
