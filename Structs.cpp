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


Status WriteStudent(StudentList* student_list)
{
    // the counter use to control the circulation depth
    static int counter = 0;
    int size = StudentCount(*student_list);
    StudentSet students = (StudentSet)malloc(size * sizeof(Student));
    // package them to a set
    for (int i = 0; i < size; i++)
    {
        *(students + i) = (*student_list)->data;
        *student_list = (*student_list)->next;
    }
    // start writing
    FILE* file = (FILE*)malloc(sizeof(FILE));
    errno_t err;
    if ((err = fopen_s(&file, STUDENT_BINARY_OBJ, "wb")) != 0)
    {
        if (counter++ < 3)
            return WriteStudent(student_list);
        printf("\n\t\t\t数据读取异常，请稍后重试!\n");
        system("pause");
        counter = 0;
        return ERROR;
    }

    if (fwrite(ParseToModel(&students, size), sizeof(Student_Data), size, file) != size)
    {
        if (counter++ < 3)
            return WriteStudent(student_list);
        printf("\n\t\t\t数据写入失败，请重试");
        counter = 0;
        return ERROR;
    }
    fclose(file);
    Free(file);
    // reset the counter
    counter = 0;
    return OK;
}

StudentList* ReadStudent()
{
    // the counter use to control the circulation depth
    static int counter = 0;
    // open the file
    FILE* file = (FILE*)malloc(sizeof(FILE));

    // check the file open status
    errno_t err;
    if ((err = fopen_s(&file, STUDENT_BINARY_OBJ, "rb")) != 0)
    {
        fclose(file);
        if ((err = fopen_s(&file, STUDENT_BINARY_OBJ, "w")) != 0)
        {
            fclose(file);
            // control the circulation depth, if this function was repeated more than 3 times, that means something other wrong
            if (counter++ < 3)
                return ReadStudent();
            printf("\n\t\t\t读取文件异常，请检查系统是否正常");
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
        StudentSet student_set = ParseToObject(students, size);
        // then create and init a new list
        StudentList student_list = (StudentList)malloc(sizeof(StudentNode));
        InitStudentList(&student_list);
        // and put the data into the list one by one
        while (student_set != NULL)
        {
            StudentNode student_node = {
                student_set->id,
                student_set->name,
                student_set->sex,
                student_set->lessons,
                student_set->address
            };
            AddStudentToList(&student_node, &student_list);
        }

        // free the memory of the student set
        Free(student_set);

        fclose(file);
        Free(file);

        // reset the counter
        counter = 0;

        return &student_list;
    }

    // don't forget close and free the file stream!
    fclose(file);
    Free(file);

    // reset the counter
    counter = 0;
    return NULL;
}


void SetLessonScore(Student* student, String lesson_name, float score)
{
    LessonNode* lesson_ptr = student->lessons->next;
    do
    {
        if (lesson_ptr->data.name == lesson_name)
        {
            lesson_ptr->data.score = score;
            lesson_ptr = NULL;
            return;
        }
        lesson_ptr = lesson_ptr->next;
    }
    while (lesson_ptr->next != NULL);
    lesson_ptr = NULL;
    printf("\n\t\t\t没有找到[%s]这门课噢!", lesson_name);
}

float GetLessonScore(Student* student, String lesson_name)
{
    LessonNode* lesson_ptr = student->lessons->next;
    do
    {
        if (lesson_ptr->data.name == lesson_name)
        {
            float result = lesson_ptr->data.score;
            lesson_ptr = NULL;
            return result;
        }
        lesson_ptr = lesson_ptr->next;
    }
    while (lesson_ptr->next != NULL);
    lesson_ptr = NULL;
    printf("\n\t\t\t没有找到[%s]这门课噢!", lesson_name);
    return -1;
}

int StudentCount(StudentList student_list)
{
    int count = 0;
    while (student_list->next != NULL)
    {
        count++;
    }
    return count;
}

void InitStudentList(StudentList* student_list)
{
    (*student_list)->data = {
        NOT_ID,
        NULL,
        '\0',
        NULL,
        NULL
    };
    (*student_list)->next = NULL;
}

void CheckId(StudentNode* student, StudentList* student_list)
{
    if (student->data.id == NOT_ID)
    {
        if (student_list == NULL || *student_list == NULL)
        {
            student->data.id = (*student_list)->next->data.id + 1;
            return;
        }
        student->data.id = (*student_list)->data.id + 1;
    }
}

void AddStudentToList(StudentNode* student, StudentList* student_list)
{
    student->next = (*student_list)->next
        (*student_list)->next = student;
}

Student* GetStudent(int id, StudentList* student_list)
{
    StudentList* tmp_ptr = student_list;
    while ((*student_list)->next != NULL)
    {
        if ((*tmp_ptr)->data.id == id)
        {
            return &(*tmp_ptr)->data;
        }
    }
    return NULL;
}

StudentNode CreateNewStudentNode(Student student)
{
    StudentNode student_node;
    student_node.data = student;
    student_node.next = NULL;
    return student_node;
}

Student_Data_Set ParseToModel(StudentSet* students, int size)
{
    Student_Data_Set student_data = (Student_Data_Set)malloc(sizeof(Student_Data) * size);
    for (int i = 0; i < size; i++)
    {
        student_data[i].id = students[i]->id;
        strcpy_s(student_data[i].name, strlen(students[i]->name), students[i]->name);
        student_data[i].sex = students[i]->sex;
        int count = 0;
        while (count < 20)
        {
            if (students[i]->lessons[count].data.name[0] != '\0')
            {
                strcpy_s(student_data[i].lessons[count].name,
                         strlen(students[i]->lessons[count].data.name),
                         students[i]->lessons[count].data.name);
                student_data[i].lessons[count].score = students[i]->lessons[count].data.score;
            }
        }
        strcpy_s(student_data[i].address, strlen(students[i]->address), students[i]->address);
    }
    ReleaseStudentSetMemory(students);
    return student_data;
}

void ReleaseStudentSetMemory(StudentSet* student)
{
    while (student == NULL)
    {
        if ((*student)->name != NULL)
        {
            Free((*student)->name);
        }
        if ((*student)->lessons != NULL)
        {
            while ((*student)->lessons->next == NULL)
            {
                if ((*student)->lessons->data.name)
                {
                    Free((*student)->lessons->data.name);
                }
                Free((*student)->lessons);
            }
        }
        if ((*student)->address != NULL)
        {
            Free((*student)->address);
        }
        student++;
    }
    Free(student);
}

StudentSet ParseToObject(Student_Data_Set* student_data_set, int size)
{
    StudentSet student_set = CreateStudentSet(size);
    for (int i = 0; i < size; i++)
    {
        student_set[i].id = student_data_set[i]->id;
        strcpy_s(student_set[i].name, strlen(student_data_set[i]->name), student_data_set[i]->name);
        student_set[i].sex = student_data_set[i]->sex;
        int count = 0;
        while (count < 20)
        {
            if (student_data_set[i]->lessons[count].name[0] != NULL)
            {
                strcpy_s(student_set[i].lessons[count].data.name,
                         strlen(student_data_set[i]->lessons[count].name),
                         student_data_set[i]->lessons[count].name);
                student_set[i].lessons[count].data.score = student_data_set[i]->lessons[count].score;
            }
        }
        strcpy_s(student_set[i].address, strlen(student_data_set[i]->address), student_data_set[i]->address);
    }
    ReleaseStudentDataSetMemory(student_data_set);
    return student_set;
}

void ReleaseStudentDataSetMemory(Student_Data_Set* student_data)
{
    while ((*student_data) != NULL)
    {
        Free(student_data);
        student_data++;
    }
}

StudentSet CreateStudentSet(int size)
{
    StudentSet student_set = (StudentSet)malloc(sizeof(Student) * size);
    for (int i = 0; i < size; i++)
    {
        student_set->id = NOT_ID;
    }
    return student_set;
}

int LessonCount(LessonList lesson_list)
{
    int count = 0;
    while (lesson_list->next != NULL)
    {
        count++;
    }
    return count;
}

LessonList CreateNewLessonList()
{
    LessonList lesson_list = (LessonList)malloc(sizeof(LessonNode));
    lesson_list->data;
    lesson_list->next = NULL;
    return lesson_list;
}

Student_Data_Set CreateStudentDataSet(int size)
{
    Student_Data_Set student_set = (Student_Data_Set)malloc(sizeof(Student_Data) * size);
    return student_set;
}
