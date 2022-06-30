#include <ctime>

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

/**
 * \brief check a student already has the lesson or not
 * \param student the student will be checked
 * \param lesson_name the lesson name
 * \return is exist or not
 */
Bool CheckLessonIsExist(Student student, String lesson_name);

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

Bool CheckLessonIsExist(Student student, String lesson_name)
{
    LessonNode* lesson_ptr = student.lessons;
    while (lesson_ptr->next != NULL)
    {
        if (lesson_name == lesson_ptr->next->data.name)
        {
            return TRUE;
        }
        lesson_ptr = lesson_ptr->next;
    }
    return FALSE;
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

    StudentList student_list = *ReadStudent();

    if (EnsuretheOparation() == YES && RemoveStudent(id, &student_list) == OK && WriteStudent(&student_list) == OK)
    {
        if (student_list != NULL)
        {
            ReleaseStudentListMemory(&student_list);
        }
        printf("\n\t\t\t删除学生信息成功!\n\t\t\t");
        system("pause");
    }
    else
    {
        if (student_list != NULL)
        {
            ReleaseStudentListMemory(&student_list);
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

    Student* student = GetStudent(id, student_list);

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
    StudentList student_list = *ReadStudent();
    StudentNode* student_ptr = student_list;
    while (student_ptr->next != NULL)
    {
        ShowStudent(student_ptr->next->data);
        student_ptr = student_ptr->next;
    }

    if (student_list->next == NULL)
    {
        printf("\n\n\t\t\t未搜索到任何数据");
    }

    if (student_list != NULL)
    {
        ReleaseStudentListMemory(&student_list);
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

    StudentList student_list = *ReadStudent();

    Student* student = GetStudent(request->id, &student_list);

    switch (request->dataType)
    {
    case NAME:
        if (student->name != NULL)
        {
            free(student->name);
        }
        student->name = (String)malloc(sizeof(char) * (strlen(request->data.str_data) + 1));
        strcpy_s(student->name, strlen(request->data.str_data) + 1, request->data.str_data);
        break;
    case CLASS:
        if (student->clazz != NULL)
        {
            free(student->clazz);
        }
        student->clazz = (String)malloc(sizeof(char) * (strlen(request->data.str_data) + 1));
        strcpy_s(student->clazz, strlen(request->data.str_data) + 1, request->data.str_data);
        break;
    case SEX:
        student->sex = request->data.char_data;
        break;
    case LESSON:
        if (student == NULL)
        {
            printf("没有找到该学生！");
            break;
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
        if (student->address != NULL)
        {
            free(student->address);
        }
        student->address = (String)malloc(sizeof(char) * (strlen(request->data.str_data) + 1));
        strcpy_s(student->address, strlen(request->data.str_data) + 1, request->data.str_data);
        break;
    }

    WriteStudent(&student_list);

    if (student_list != NULL)
    {
        ReleaseStudentListMemory(&student_list);
    }

    printf("\n\n\t\t\t修改学生数据成功!");

    printf("\n\n\t\t\t");
    system("pause");

    StudentInfoWindow();
}

void SearchAllScore()
{
    system("CLS");

    StudentList student_list = *ReadStudent();

    SortLessonList sort_lesson_list = *ParseToSortingList(&student_list);

    if (sort_lesson_list->next == NULL)
    {
        printf("\n\n\t\t\t目前没有任何课程成绩噢");
    }

    SortLessonList result_list = *CreateNewSortingList();
    while (sort_lesson_list->next != NULL)
    {
        SortLessonNode* sort_ptr = sort_lesson_list;
        SortLessonNode* max_node = NULL;
        SortLessonNode* prior = NULL;
        if (sort_ptr->next == NULL)
        {
            break;
        }
        while (sort_ptr->next != NULL)
        {
            // each turn will find the node has max score and add it to result list
            if (max_node == NULL || max_node->score < sort_ptr->next->score)
            {
                max_node = sort_ptr->next;
                prior = sort_ptr;
            }
            sort_ptr = sort_ptr->next;
        }
        // let the next pointer of the prior node of the max node point to the next node of the max node
        prior->next = max_node->next;
        // let the next pointer of the max node point to null(cut off the relationship between max node and the base list)
        max_node->next = NULL;
        // create a new node and add it to result list
        SortLessonNode* tmp_node = CreateNewSortingNode();
        tmp_node->lesson_name = (String)malloc(sizeof(char) * (strlen(max_node->lesson_name) + 1));
        tmp_node->student_name = (String)malloc(sizeof(char) * (strlen(max_node->student_name) + 1));
        strcpy_s(tmp_node->lesson_name, strlen(max_node->lesson_name) + 1, max_node->lesson_name);
        strcpy_s(tmp_node->student_name, strlen(max_node->student_name) + 1, max_node->student_name);
        tmp_node->score = max_node->score;
        tmp_node->next = NULL;
        // add the max node into the result list
        AddSortingNodeToList(tmp_node, &result_list);
    }

    if (sort_lesson_list != NULL)
    {
        ReleaseTheSortingList(&sort_lesson_list);
    }

    ShowSortingList(&result_list, ASC);
}

void SearchScoreByStudent()
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

    Student* student = GetStudent(id, student_list);

    if (student == NULL)
    {
        printf("\n\n\t\t\t没有找到学号为 %llu 的学生的信息...", id);
        printf("\n\n\t\t\t");
        system("pause");
        return ScoreManagerWindow();
    }

    printf("\n\n\t\t\t学号: %llu", student->id);
    printf("\n\t\t\t姓名: %s", student->name);

    if (student->lessons->next == NULL)
    {
        printf("\n\n\t\t\t该学生当前没有课程\n");
    }
    else
    {
        printf("\n\t\t\t该学生当前的所有课程:");
        LessonNode* lesson_ptr = student->lessons;
        while (lesson_ptr->next != NULL)
        {
            printf("\n\t\t\t\t课程名: %s", lesson_ptr->next->data.name);
            printf("\n\t\t\t\t成绩: %d分\n", lesson_ptr->next->data.score);
            lesson_ptr = lesson_ptr->next;
        }
    }

    if (student_list != NULL)
    {
        ReleaseStudentListMemory(student_list);
    }
    student_list = NULL;
    student = NULL;

    printf("\n\n\t\t\t");

    system("pause");

    ScoreManagerWindow();
}

void SearchScoreByLesson()
{
    system("CLS");

    printf("\n\n\t\t\t请输入你想要查询的科目:");

    String lesson_name = CheckAndGetInput(30);

    StudentList student_list = *ReadStudent();

    StudentNode* student_ptr = student_list;

    SortLessonList sort_lesson_list = *CreateNewSortingList();

    // find all the lesson which named 'lesson_name'
    while (student_ptr->next != NULL)
    {
        LessonNode* lesson_ptr = student_ptr->next->data.lessons;
        while (lesson_ptr->next != NULL)
        {
            if (strcmp(lesson_ptr->next->data.name, lesson_name) == 0)
            {
                SortLessonNode* tmp_node = CreateNewSortingNode();
                tmp_node->lesson_name = (String)malloc(sizeof(char) * (strlen(lesson_ptr->next->data.name) + 1));
                tmp_node->student_name = (String)malloc(sizeof(char) * (strlen(student_ptr->next->data.name) + 1));
                strcpy_s(tmp_node->student_name, strlen(student_ptr->next->data.name) + 1,
                         student_ptr->next->data.name);
                strcpy_s(tmp_node->lesson_name, strlen(lesson_ptr->next->data.name) + 1, lesson_ptr->next->data.name);
                tmp_node->score = lesson_ptr->next->data.score;
                AddSortingNodeToList(tmp_node, &sort_lesson_list);
                break;
            }
            lesson_ptr = lesson_ptr->next;
        }
        student_ptr = student_ptr->next;
    }

    if (student_list != NULL)
        ReleaseStudentListMemory(&student_list);

    ShowSortingList(&sort_lesson_list, ASC);

    DataController(&sort_lesson_list);

    if (sort_lesson_list != NULL)
        ReleaseTheSortingList(&sort_lesson_list);

    ScoreManagerWindow();
}

void UpdateStudentScore()
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
    request->dataType = LESSON;
    for (int i = 0; i < size; i++)
    {
        request->id += (id_str[i] - '0') * (unsigned long long)pow(10, size - i - 1);
    }

    printf("\n\n\t\t\t请输入该课程的课程名:");
    request->data.lesson_data = {(String)malloc(sizeof(char) * 30), -1};
    strcpy_s(request->data.lesson_data.name, 30, CheckAndGetInput(30));
    printf("\n\t\t\t请输入该课程的分数:");
    String tmp_string = (String)malloc(sizeof(char) * 30);
    scanf_s("%s", tmp_string);
    Bool is_float = TRUE;
    for (int i = 0; i < strlen(tmp_string); i++)
    {
        if ((tmp_string[i] < '0' || tmp_string[i] > '9') && tmp_string[i] != '.')
        {
            is_float = FALSE;
        }
    }
    while (!is_float)
    {
        printf("\n\t\t\t请输入正确的数据!\n\t\t\t");
        scanf_s("%s", tmp_string);
        is_float = TRUE;
        for (int i = 0; i < strlen(tmp_string); i++)
        {
            if ((tmp_string[i] < '0' || tmp_string[i] > '9') && tmp_string[i] != '.')
            {
                is_float = FALSE;
            }
        }
    }
    request->data.lesson_data.score = StringToFloat(tmp_string);

    StudentList student_list = *ReadStudent();

    Student* student = GetStudent(request->id, &student_list);

    if (student == NULL)
    {
        printf("\n\n\t\t\t未找到相应的学生, 请重新输入学号!\n\t\t\t");
        system("pause");        
    }

    if (SetLessonScore(student, request->data.lesson_data.name, request->data.lesson_data.score) != OK)
    {
        // handle the exception
        printf("\n\t\t\t没有找到这门课噢!");
        printf("\n\n\t\t\t是否要给该学生添加课程(1: 是; 2: 否)？");
        int order;
        do
        {
            order = GetOrderInput();
        }
        while (order != 1 && order != 2);
        if (order == 1)
        {
            LessonNode* lesson_node = (LessonNode*)malloc(sizeof(LessonNode));
            lesson_node->next = NULL;
            lesson_node->data.name = (String)malloc(sizeof(char) * (strlen(request->data.lesson_data.name) + 1));
            strcpy_s(lesson_node->data.name, strlen(request->data.lesson_data.name) + 1,
                     request->data.lesson_data.name);
            AddLessonToList(lesson_node, &student->lessons);
        }
    }
    if (WriteStudent(&student_list) == OK)
    {
        printf("\n\n\t\t\t修改学生成绩成功!\n\t\t\t");
        system("pause");
    }
    else
    {
        printf("\n\n\t\t\t修改学生成绩失败，请查看输入信息是否有误!\n");
        system("pause");
    }

    if (student_list != NULL)
    {
        ReleaseStudentListMemory(&student_list);
    }

    ScoreManagerWindow();
}

void AddLessonForStudent()
{
    system("CLS");

    printf("\n\n\t\t\t请选择为班级或为学生个人添加课程(1. 班级; 2. 学生):");

    int order;
    do
    {
        order = GetOrderInput();
    }
    while (order != 1 && order != 2);
    printf("\n\n\t\t\t请输入要添加课程的课程名:");
    String lesson_name = CheckAndGetInput(30);
    StudentList student_list = *ReadStudent();
    if (order == 1)
    {
        printf("\n\n\t\t\t请输入想要添加的班级:");
        String clazz = CheckAndGetInput(20);
        StudentNode* student_ptr = student_list;
        while (student_ptr->next != NULL)
        {
            if ((student_ptr->next->data.clazz = clazz))
            {
                LessonNode* lesson_node = (LessonNode*)malloc(sizeof(LessonNode));
                lesson_node->data.name = (String)malloc(sizeof(char) * 30);
                strcpy_s(lesson_node->data.name, strlen(lesson_name) + 1, lesson_name);
                // -1 on behalf of the student has no score
                lesson_node->data.score = -1.0;
                AddLessonToList(lesson_node, &student_ptr->next->data.lessons);
            }
            student_ptr = student_ptr->next;
        }
    }
    else
    {
        printf("\n\n\t\t\t请输入想要添加的学生学号(请不要输入非数字的字符, 因为那将视为学号的结束符):");
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
        int id = 0;
        for (int i = 0; i < size; i++)
        {
            id += (id_str[i] - '0') * (unsigned long long)pow(10, size - i - 1);
        }

        Student* student = GetStudent(id, &student_list);
        if (student == NULL)
        {
            printf("\n\n\t\t\t未找到相应的学生\n");

            system("pause");

            return ScoreManagerWindow();
        }
        LessonNode* lesson_node = (LessonNode*)malloc(sizeof(LessonNode));
        lesson_node->data.name = (String)malloc(sizeof(char) * (strlen(lesson_name) + 1));
        strcpy_s(lesson_node->data.name, strlen(lesson_name) + 1, lesson_name);
        // -1 on behalf of the student has no score
        lesson_node->data.score = -1.0;
        lesson_node->next = NULL;
        if (!CheckLessonIsExist(*student, lesson_name))
            AddLessonToList(lesson_node, &student->lessons);
    }

    if (WriteStudent(&student_list) == OK)
    {
        printf("\n\n\t\t\t添加课程成功！");
    }
    else
    {
        printf("\n\n\t\t\t添加课程失败");
    }

    system("pause");

    ScoreManagerWindow();
}
