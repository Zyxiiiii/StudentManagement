#include "AllHeader.h"

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
    String data_keeper;
    do
    {
        printf("\n\t\t\t请输入正确的性别(男/女):");
        data_keeper = CheckAndGetInput(3);
    }
    while (strcmp(data_keeper, "男") != 0 && strcmp(data_keeper, "女") != 0);
    student.data.sex = strcmp(data_keeper, "女") == 0 ? WOMEN : MAN;
    printf("\n\t\t\t请输入该学生的住址(30字以内):");
    data_keeper = CheckAndGetInput(30 * 2);
    strcpy_s(student.data.address, 30 * 2, data_keeper);

    StudentList student_list = *ReadStudent();

    student.data.id = GetMaxId(student_list) + 1;

    AddStudentToList(&student, &student_list);

    if (WriteStudent(&student_list) == OK)
    {
        if (student_list == NULL)
        {
            ReleaseStudentListMemory(&student_list);
        }
        printf("\n\t\t\t新增学生成功\n\n\t\t\t");
        system("pause");
    }
    else
    {
        if (student_list == NULL)
        {
            ReleaseStudentListMemory(&student_list);
        }
        printf("\n\t\t\t新增学生失败\n\n\t\t\t");
        system("pause");
    }


    StudentInfoWindow();
}

void DeleteStudent()
{
    system("CLS");

    printf("\n\n\t\t\t请输入想要删除的学生学号(请不要输入非数字的字符, 因为那将视为学号的结束符):");
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
        if (*student_list != NULL)
        {
            ReleaseStudentListMemory(student_list);
        }
        printf("\n\t\t\t删除学生信息成功!\n\t\t\t");
        system("pause");
    }
    else
    {
        if (*student_list != NULL)
        {
            ReleaseStudentListMemory(student_list);
        }
        printf("\n\t\t\t删除学生信息失败!\n\n\t\t\t请检查输入的id是否正确\n\t\t\t");
        system("pause");
    }


    StudentInfoWindow();
}

void SearchStudent()
{
    system("CLS");

    printf("\n\n\t\t\t请输入想要查询的学生学号(请不要输入非数字的字符, 因为那将视为学号的结束符):");
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

    Student* student = GetStudent(id, *student_list);

    if (student != NULL)
    {
        ShowStudent(*student);
    }
    else
    {
        printf("\n\t\t\t未找到该学生信息...");
    }

    if (*student_list != NULL)
    {
        ReleaseStudentListMemory(student_list);
    }

    printf("\n\t\t\t");
    system("pause");

    StudentInfoWindow();
}

void ShowAllStudent()
{
    system("CLS");
    StudentList* student_list = ReadStudent();
    while ((*student_list)->next != NULL)
    {
        ShowStudent((*student_list)->next->data);
        *student_list = (*student_list)->next;
    }

    if ((*student_list) != NULL)
    {
        ReleaseStudentListMemory(student_list);
        student_list = NULL;
    }

    printf("\n\t\t\t");

    system("pause");

    StudentInfoWindow();
}

void UpdateStudentInfo()
{
    system("CLS");

    printf("\n\n\t\t\t请输入想要修改的学生学号(请不要输入非数字的字符, 因为那将视为学号的结束符):");
    // build the update request body
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
    UpdateRequest* request = (UpdateRequest*)malloc(sizeof(UpdateRequest));
    request->id = 0;
    for (int i = 0; i < size; i++)
    {
        request->id += (id_str[i] - '0') * (unsigned long long)pow(10, size - i - 1);
    }

    printf("\n\t\t\t1. 姓名");
    printf("\n\n\t\t\t2. 班别");
    printf("\n\n\t\t\t3. 性别");
    printf("\n\n\t\t\t4. 课程");
    printf("\n\n\t\t\t5. 住址");
    printf("\n\n\t\t\t请输入想要修改的信息:");

    int order;
    do
    {
        order = GetOrderInput();
    }
    while (order > 5 || order <= 0);

    request->dataType = (DataType)order;

    switch (order)
    {
    // handle the different order
    case NAME:
        {
            printf("\n\n\t\t\t请输入该学生的名字(大于一个字，16个字以内):");
            request->data.str_data = (String)malloc(sizeof(char) * 16 * 2);
            strcpy_s(request->data.str_data, 16 * 2, CheckAndGetInput(16 * 2));
            break;
        }
    case CLASS:
        {
            printf("\n\n\t\t\t请输入该学生的班别(格式为英文缩写+年级+班号):");
            request->data.str_data = (String)malloc(sizeof(char) * 20);
            strcpy_s(request->data.str_data, 20, CheckAndGetInput(20));
            break;
        }
    case SEX:
        {
            String data_keeper;
            do
            {
                printf("\n\n\t\t\t请输入正确的性别(男/女):");
                data_keeper = CheckAndGetInput(3);
            }
            while (strcmp(data_keeper, "男") != 0 && strcmp(data_keeper, "女") != 0);
            request->data.char_data = strcmp(data_keeper, "男") == 0 ? MAN : WOMEN;
            break;
        }
    case LESSON:
        {
            printf("\n\n\t\t\t请输入该课程的课程名:");
            request->data.lesson_data = {(String)malloc(sizeof(char) * 30), -1};
            strcpy_s(request->data.lesson_data.name, 30, CheckAndGetInput(30));
            printf("\n\t\t\t请输入该课程的分数(请不要输入非数字, 且最大为3位数):");
            String input_check = CheckAndGetInput(3);
            char score_payload[4] = {0};
            for (int i = 0; i < 4; i++)
            {
                if (3 == i)
                {
                    score_payload[i] = '\0';
                    break;
                }
                int num = input_check[i] - '0';
                if (num >= 0 && num <= 9)
                {
                    score_payload[i] = input_check[i];
                }
                else
                {
                    score_payload[i] = '\0';
                    break;
                }
            }
            int size = strlen(score_payload);
            request->data.lesson_data.score = 0;
            for (int i = 0; i < size; i++)
            {
                request->data.lesson_data.score += (int)((score_payload[i] - '0') * pow(10, size - i - 1));
            }
            break;
        }
    case ADDRESS:
        {
            printf("\n\t\t\t请输入该学生的住址(30字以内):");
            request->data.str_data = (String)malloc(sizeof(char) * 30 * 2);
            strcpy_s(request->data.str_data, 30 * 2, CheckAndGetInput(30 * 2));
            break;
        }
    default:
        {
            printf("\n\t\t\t数据异常, 请重试");
            printf("\n\n\t\t\t");
            system("pause");
            if (request != NULL)
                ReleaseRequestMemory(request);
            StudentInfoWindow();
        }
    }

    StudentList* student_list = ReadStudent();

    Student* student = GetStudent(request->id, *student_list);

    switch (request->dataType)
    {
    case NAME:
        strcpy_s(student->name, strlen(request->data.str_data) + 1, request->data.str_data);
        break;
    case CLASS:
        strcpy_s(student->clazz, strlen(request->data.str_data) + 1, request->data.str_data);
        break;
    case SEX:
        student->sex = request->data.char_data;
        break;
    case LESSON:
        if (*student_list != NULL)
        {
            ReleaseStudentListMemory(student_list);
        }

        if (SetLessonScore(student, request->data.lesson_data.name, request->data.lesson_data.score) != OK)
        {
            // handle the exception
            printf("\n\t\t\t没有找到这门课噢!");
            printf("\n\n\t\t\t请重试");
            return StudentInfoWindow();
        }
        break;
    case ADDRESS:
        strcpy_s(student->address, strlen(request->data.str_data) + 1, request->data.str_data);
        break;
    }

    WriteStudent(student_list);

    if (*student_list != NULL)
    {
        ReleaseStudentListMemory(student_list);
    }

    printf("\n\n\t\t\t修改学生数据成功!");

    printf("\n\n\t\t\t");
    system("pause");

    StudentInfoWindow();
}

void SearchAllScore()
{
    system("CLS");

    StudentList* student_list = ReadStudent();

    StudentNode* student_ptr = *student_list;

    Bool has_class = FALSE;

    while (student_ptr->next != NULL)
    {
        printf("\n\n\t\t\t%s的成绩为:", student_ptr->next->data.name);
        LessonNode* lesson_ptr = student_ptr->next->data.lessons;
        while (lesson_ptr->next != NULL)
        {
            has_class = TRUE;
            printf("\n\t\t\t%s: %.1f分", lesson_ptr->next->data.name, lesson_ptr->next->data.score);
            lesson_ptr = lesson_ptr->next;
        }
        student_ptr = student_ptr->next;
    }

    if (!has_class)
    {
        printf("\n\n\t\t\t目前没有任何课程成绩噢");
    }
}
