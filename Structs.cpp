#include <ctime>
#include <xutility>

#include "AllHeader.h"

// private declaration

// the path of the student object
#define STUDENT_BINARY_OBJ "student.data"

#ifndef STUDENT_PRIVATE_DEF

#define STUDENT_PRIVATE_DEF

/**
 * \brief init tht student list
 */
void InitStudentList(StudentList* student_list);

void CheckId(StudentNode* student, StudentList student_list);
#endif // !STUDENT_PRIVATE_DEF


#ifndef LESSON_PRIVATE_DEF

#define LESSON_PRIVATE_DEF

#endif


Status WriteStudent(StudentList student_list)
{
    // ensure it will begin at head node
    student_list = student_list->head;
    int size = StudentCount(student_list);
    StudentSet students = (StudentSet)malloc(size * sizeof(Student));
    // package them to a set
    for (int i = 0; i < size; i++)
    {
        *(students + i) = student_list->data;
        student_list = student_list->next;
    }
    // start writing
    FILE* file = (FILE*)malloc(sizeof(FILE));
    errno_t err;
    if ((err = fopen_s(&file, STUDENT_BINARY_OBJ, "wb")) != 0)
    {
        printf("\n\t\t\t数据读取异常，请稍后重试!\n");
        system("pause");
        exit(err);
    }

    if (fwrite(ParseToModel(students, size), sizeof(Student_Data), size, file) != size)
    {
        printf("数据写入失败，请重试");
    }
    fclose(file);
    return OK;
}

void ReadStudent()
{
    FILE* file = (FILE*)malloc(sizeof(FILE));

    errno_t err;

    if ((err = fopen_s(&file, STUDENT_BINARY_OBJ, "rb")) != 0)
    {
        if ((err = fopen_s(&file, STUDENT_BINARY_OBJ, "w")) != 0)
        {
            fclose(file);
            ReadStudent();
            return;
        }
    }

    // move the file ptr point to the end of the file,
    // and get it position to know the size of this file,
    // than could get the size of the student through the file's size divide by the student's size at last
    fseek(file, 0L, SEEK_END);
    int size = ftell(file) / sizeof(Student_Data);
    fseek(file, 0L, SEEK_SET);
    if (size != 0)
    {
        Student_Data_Set students = CreateStudentDataSet(size);
        // first read the binary data in file, it will be pack in a student set
        fread(students, sizeof(Student_Data), size, file);

        // next use the function ParseToObject to parse this data to the struct we use in usual
        StudentSet _student_set = ParseToObject(students, size);
        // then create and init a new list
        StudentList _student_List;
        // and put the data into the list one by one
        StudentNode head_node = CreateNewStudent();
        head_node.data = _student_set[0];
        _student_List = &head_node;
        for (int i = 1; i < size; i++)
        {
            StudentNode student_node = CreateNewStudent();
            student_node.next = _student_List->head;
            student_node.data = _student_set[i];
            _student_List->head = &student_node;
        }

        // 回到顶部
        _student_List = _student_List->head;

        global_student_list = _student_List;
    }

    fclose(file);
}


void SetLessonScore(Student* student, String lesson_name, float score)
{
    LessonList lesson_list = student->lessons;
    if (lesson_name == lesson_list->data.name)
    {
        lesson_list->data.score = score;
        return;
    }
    printf("\t\t\t没有找到[%s]这门课噢!", lesson_name);
}

float GetLessonScore(Student* student, String lesson_name)
{
    LessonList class_list = student->lessons;
    if (lesson_name == class_list->data.name)
    {
        return class_list->data.score;
    }
    printf("\t\t\t没有找到[%s]这门课噢!", lesson_name);
    return -1;
}

int StudentCount(StudentList student_list)
{
    if (student_list == NULL)
    {
        return 0;
    }
    int count = 1;

    student_list = student_list->head;

    while (student_list->next != NULL)
    {
        student_list = student_list->next;
    }

    return count;
}

void InitStudentList(StudentList* student_list)
{
    (*student_list)->head = *student_list;
    (*student_list)->next = NULL;
}

void CheckId(StudentNode* student, StudentList student_list)
{
    if ((*student).data.id == NOT_ID)
    {
        int tmp = rand();
        // let this ptr point to head node
        while (student_list != NULL && student_list->next != NULL)
        {
            if (tmp == student->data.id)
            {
                CheckId(student, student_list);
                return;
            }
            student = student->next;
        }
        (*student).data.id = tmp;
    }
}

void AddStudentToList(StudentNode* student, StudentList student_list)
{
    CheckId(student, student_list);

    if (student_list == NULL)
    {
        student_list = student;
        InitStudentList(&student_list);
        if (WriteStudent(student_list) == OK)
        {
            printf("\t\t\t保存数据成功！");
            system("pause");
        }
        else
        {
            printf("\t\t\t保存数据失败，请稍后重试.");
            system("pause");
        }
        return;
    }

    student->next = student_list->head;
    student_list->head = student;

    // save data
    if (WriteStudent(student_list) == OK)
    {
        printf("\t\t\t保存数据成功！");
        system("pause");
    }
    else
    {
        printf("\t\t\t保存数据失败，请稍后重试.");
        system("pause");
    }
}

Student* GetStudent(int id, StudentList student_list)
{
    while (student_list->next != NULL)
    {
        if (student_list->data.id == id)
        {
            return &student_list->data;
        }
    }

    printf("\t\t\t没有找到id为:%d的学生", id);

    return NULL;
}

StudentNode CreateNewStudent()
{
    Student student_data{
        NOT_ID,
        (String)malloc(16 * sizeof(char)),
        MAN,
        NULL,
        (String)malloc(sizeof(char) * 30)
    };
    StudentNode* student = (StudentNode*)malloc(sizeof(StudentNode));
    student->head = student;
    student->data = student_data;
    student->next = NULL;
    return *student;
}

Student_Data_Set ParseToModel(StudentSet students, int size)
{
    Student_Data_Set student_data = (Student_Data_Set)malloc(sizeof(Student_Data) * size);
    for (int i = 0; i < size; i++)
    {
        student_data[i].id = students[i].id;
        strcpy_s(student_data[i].name, 32, students[i].name);
        student_data[i].sex = students[i].sex;
        int count = 0;
        do
        {
            if (LessonCount(students[i].lessons) == 0)
            {
                break;
            }
            if (students[i].lessons[count].data.name[29] != '\0')
            {
                continue;
            }
            strcpy_s(student_data[i].lessons[count].name, 30, students[i].lessons[count].data.name);
            student_data[i].lessons[count].score = students[i].lessons[count].data.score;
        }
        while (students[i].lessons[count++].next != NULL);
        strcpy_s(student_data[i].address, 60, students[i].address);
    }
    return student_data;
}

StudentSet ParseToObject(Student_Data_Set student_data_set, int size)
{
    StudentSet student_set = CreateStudentSet(size);
    for (int i = 0; i < size; i++)
    {
        student_set[i].id = student_data_set[i].id;
        strcpy_s(student_set[i].name, 33, student_data_set[i].name);
        student_set[i].sex = student_data_set[i].sex;
        int count = 0;
        do
        {
            // has no lesson
            if (student_data_set[i].lessons == NULL)
            {
                break;
            }
            // this lesson was not set
            if (student_data_set[i].lessons[count].name[29] != '\0')
            {
                continue;
            }
            strcpy_s(student_set[i].lessons[count].data.name, 30, student_data_set[i].lessons[count].name);
            student_set[i].lessons[count].data.score = student_data_set[i].lessons[count].score;
        }
        while (count++ < 20);
        strcpy_s(student_set[i].address, 61, student_data_set[i].address);
    }
    return student_set;
}

StudentSet CreateStudentSet(int size)
{
    StudentSet student_set = (StudentSet)malloc(sizeof(Student) * size);
    for (int i = 0; i < size; i++)
    {
        student_set[i].id = NOT_ID;
        student_set[i].name = (String)malloc(sizeof(char) * 32);
        student_set[i].sex = '\0';
        student_set[i].lessons = (LessonList)malloc(sizeof(LessonNode) * 20);
        int count = 0;
        while (count < 20)
        {
            student_set[i].lessons[count].head = &student_set[i].lessons[count];
            student_set[i].lessons[count].next = NULL;
            student_set[i].lessons[count++].data = {(String)malloc(sizeof(char) * 30), 0};
        }
        student_set[i].address = (String)malloc(sizeof(char) * 60);
    }
    return student_set;
}

int LessonCount(LessonList lesson_list)
{
    if (lesson_list == NULL)
    {
        return 0;
    }
    int count = 1;

    lesson_list = lesson_list->head;

    while (lesson_list->next != NULL)
    {
        lesson_list = lesson_list->next;
    }

    return count;
}

LessonList CreateNewLessonList(Lesson lesson)
{
    LessonList lesson_list = (LessonList)malloc(sizeof(LessonNode));
    lesson_list->head = lesson_list;
    lesson_list->data = lesson;
    lesson_list->next = NULL;
    return lesson_list;
}

Student_Data_Set CreateStudentDataSet(int size)
{
    Student_Data_Set student_set = (Student_Data_Set)malloc(sizeof(Student_Data) * size);
    return student_set;
}
