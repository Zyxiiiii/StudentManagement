#include "AllHeader.h"

// private declaration

// the path of the student object
#define STUDENT_BINARY_OBJ "./student.obj"

#ifndef STUDENT_PRIVATE_DEF

#define STUDENT_PRIVATE_DEF

/**
 * \brief move the student to his next node
 * \param student student node
 */
void ToNextNode(StudentNode* student);

/**
 * \brief init tht student list
 */
void InitStudentList(StudentList);


#endif // !STUDENT_PRIVATE_DEF


Status WriteStudent(StudentList student_list)
{
    // ensure it will begin at head node
    student_list = student_list->head;
    int size = StudentCount(student_list);
    StudentSet students = (StudentSet)malloc(size * sizeof(Student));
    // package them to a set
    for (int i = 0; i < size; i++)
    {
        *(students + size) = student_list->data;
        ToNextNode(student_list);
    }
    // start writing
    FILE** file = NULL;
    fopen_s(file, STUDENT_BINARY_OBJ, "wb");
    fwrite(students, sizeof(Student), size, *file);
    fclose(*file);
    return OK;
}

StudentList ReadStudent()
{
    FILE** file = NULL;
    fopen_s(file, STUDENT_BINARY_OBJ, "rb");

    // move the file ptr point to the end of the file,
    // and get it position to know the size of this file,
    // than could get the size of the student through the file's size divide by the student's size at last
    fseek(*file, 0L, SEEK_END);
    int size = ftell(*file) / sizeof(Student);
    StudentSet students = (StudentSet)malloc(sizeof(Student) * size);

    StudentList studentList = NULL;
    InitStudentList(studentList);
    studentList->data = *students;
    for (int i = 1; i < size; i++)
    {
        StudentNode student;
        student.data = *(students + i);
        AddStudentToList(&student, studentList);
    }

    // 回到顶部
    studentList = studentList->head;

    return studentList;
}


void SetLessonScore(Student* student, String lesson_name, float score)
{
    LessonList classList = student->lessons;
    if (lesson_name == classList->name)
    {
        classList->score = score;
        return;
    }
    printf("没有找到[%s]这门课噢!", lesson_name);
}

float GetLessonScore(Student* student, String lesson_name)
{
    LessonList classList = student->lessons;
    if (lesson_name == classList->name)
    {
        return classList->score;
    }
    printf("没有找到[%s]这门课噢!", lesson_name);
    return -1;
}


void ToNextNode(StudentNode* student)
{
    student->data = student->next->data;
    student->next = student->next->next;
}

int StudentCount(StudentList student_list)
{
    int count = 1;

    student_list = student_list->head;

    while (student_list->next != NULL)
    {
        ToNextNode(student_list);
    }

    return count;
}

void InitStudentList(StudentList student_list)
{
    student_list->head = student_list;
    student_list->next = NULL;
}

void AddStudentToList(StudentNode* student, StudentList student_list)
{
    // 头插法
    student->next = student_list->head;
    student_list->head = student;
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

    printf("没有找到id为:%d的学生", id);

    return NULL;
}
