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


Status WriteStudent(StudentList* student_list)
{
    // the counter use to control the circulation depth
    static int counter = 0;
    int size = StudentCount(*student_list);
    StudentSet students = (StudentSet)malloc(size * sizeof(Student));
    // package them to a set
    StudentNode* student_ptr = (*student_list)->next;
    for (int i = 0; i < size; i++)
    {
        students[i] = student_ptr->data;
        student_ptr = student_ptr->next;
    }
    student_ptr = NULL;
    // start writing
    FILE* file;
    errno_t err = fopen_s(&file, STUDENT_BINARY_OBJ, "wb");
    if (err != 0)
    {
        fclose(file);
        if (counter++ < 3)
            return WriteStudent(student_list);
        printf("\n\t\t\t数据读取异常，请稍后重试!\n");
        system("pause");
        counter = 0;
        return ERROR;
    }

    if (fwrite(ParseToModel(&students, size), sizeof(Student_Data), size, file) != size)
    {
        fclose(file);
        if (counter++ < 3)
            return WriteStudent(student_list);
        printf("\n\t\t\t数据写入失败，请重试");
        counter = 0;
        return ERROR;
    }
    fclose(file);
    file = NULL;
    // reset the counter
    counter = 0;
    return OK;
}

StudentList* ReadStudent()
{
    // the counter use to control the circulation depth
    static int counter = 0;
    // open the file
    FILE* file;

    // check the file open status
    errno_t err = fopen_s(&file, STUDENT_BINARY_OBJ, "rb");
    if (err != 0)
    {
        if (file != NULL)
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
        StudentSet student_set = ParseToObject(&students, size);
        // then create and init a new list
        StudentList student_list = (StudentList)malloc(sizeof(StudentNode));
        InitStudentList(&student_list);
        // and put the data into the list one by one
        int count = 0;
        while (size - count++ > 0)
        {
            StudentNode* student_node = (StudentNode*)malloc(sizeof(StudentNode));
            student_node->data.id = student_set->id;
            student_node->data.name = (String)malloc(sizeof(char) * (strlen(student_set->name) + 1));
            strcpy_s(student_node->data.name, strlen(student_set->name) + 1, student_set->name);
            student_node->data.clazz = (String)malloc(sizeof(char) * (strlen(student_set->clazz) + 1));
            strcpy_s(student_node->data.clazz, strlen(student_set->clazz) + 1, student_set->clazz);
            student_node->data.lessons = CreateNewLessonList();
            LessonList lesson_ptr = student_set->lessons->next;
            while (lesson_ptr != NULL)
            {
                LessonNode lesson_node = *lesson_ptr;
                AddLessonToList(&lesson_node, &student_node->data.lessons);
                lesson_ptr = lesson_ptr->next;
            }
            student_node->data.sex = student_set->sex;
            student_node->data.address = (String)malloc(sizeof(char) * (strlen(student_set->address) + 1));
            strcpy_s(student_node->data.address, strlen(student_set->address) + 1, student_set->address);
            student_set++;
            AddStudentToList(student_node, &student_list);
        }

        // free the memory of the student set
        student_set -= count - 1;
        free(student_set);
        student_set = NULL;

        fclose(file);
        file = NULL;

        // reset the counter
        counter = 0;

        return &student_list;
    }

    // don't forget close and free the file stream!
    fclose(file);
    file = NULL;

    // reset the counter
    counter = 0;
    StudentList new_student_list = (StudentList)malloc(sizeof(StudentNode));
    InitStudentList(&new_student_list);
    return &new_student_list;
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
        student_list = student_list->next;
    }
    return count;
}

void InitStudentList(StudentList* student_list)
{
    (*student_list)->data = {
        NOT_ID,
        NULL,
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
    student->next = (*student_list)->next;
    (*student_list)->next = student;
}

Student* GetStudent(unsigned long long id, StudentList* student_list)
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
    Student* student_ptr = *students;
    for (int i = 0; i < size; i++)
    {
        student_data[i].id = student_ptr[i].id;
        strcpy_s(student_data[i].name, strlen(student_ptr[i].name) + 1, student_ptr[i].name);
        strcpy_s(student_data[i].clazz, strlen(student_ptr[i].clazz) + 1, student_ptr[i].clazz);
        student_data[i].sex = student_ptr[i].sex;
        int count = 0;
        LessonNode* lesson_ptr = (*students)[i].lessons->next;
        while (count < 20)
        {
            if (lesson_ptr + count == NULL)
            {
                // if reach a null ptr, that means all the lesson after this index is null, so reset their data to avoid using a wrong memory 
                for (int j = 0; j < 20 - count; j++)
                {
                    student_data[i].lessons[j].name[0] = '\0';
                    student_data[i].lessons[j].score = -1.0;
                }
                break;
            }
            if ((lesson_ptr + count)->data.name[0] == '\0')
            {
                strcpy_s(student_data[i].lessons[count].name,
                         strlen((lesson_ptr + count)->data.name) + 1,
                         (lesson_ptr + count)->data.name);
                student_data[i].lessons[count].score = (lesson_ptr + count)->data.score;
                count++;
            }
        }
        strcpy_s(student_data[i].address, strlen(student_ptr[i].address) + 1, student_ptr[i].address);
    }
    ReleaseStudentSetMemory(students, size);
    return student_data;
}

void ReleaseStudentSetMemory(StudentSet* student, int size)
{
    int count = 0;
    while (count++ < size)
    {
        StudentSet student_ptr = *student + count - 1;
        if (student_ptr->name != NULL)
        {
            free(student_ptr->name);
            student_ptr->name = NULL;
        }
        if (student_ptr->clazz != NULL)
        {
            free(student_ptr->clazz);
            student_ptr->clazz = NULL;
        }
        if (student_ptr->lessons != NULL)
        {
            LessonNode* lesson_ptr = NULL;
            while (student_ptr->lessons->next != NULL)
            {
                lesson_ptr = student_ptr->lessons->next;
                if (lesson_ptr->data.name != NULL)
                {
                    free(lesson_ptr->data.name);
                    student_ptr->lessons->data.name = NULL;
                }
                student_ptr->lessons = student_ptr->lessons->next;
                free(lesson_ptr);
                lesson_ptr = NULL;
            }
            free(student_ptr->lessons);
            student_ptr->lessons = NULL;
        }
        if (student_ptr->address != NULL)
        {
            free(student_ptr->address);
            student_ptr->address = NULL;
        }
    }
    free(*student);
    *student = NULL;
    student = NULL;
}

StudentSet ParseToObject(Student_Data_Set* student_data_set, int size)
{
    StudentSet student_set = CreateStudentSet(size);
    Student_Data_Set data_ptr = *student_data_set;
    for (int i = 0; i < size; i++)
    {
        student_set[i].id = data_ptr[i].id;
        student_set[i].name = (String)malloc(sizeof(char) * (strlen(data_ptr[i].name) + 1));
        strcpy_s(student_set[i].name, strlen(data_ptr[i].name) + 1, data_ptr[i].name);
        student_set[i].clazz = (String)malloc(sizeof(char) * (strlen(data_ptr[i].clazz) + 1));
        strcpy_s(student_set[i].clazz, strlen(data_ptr[i].clazz) + 1, data_ptr[i].clazz);
        student_set[i].sex = data_ptr[i].sex;
        int count = 0;
        student_set[i].lessons = CreateNewLessonList();
        while (count < 20)
        {
            if (data_ptr[i].lessons[count].name[0] != '\0')
            {
                Lesson* lesson = (Lesson*)malloc(sizeof(Lesson));
                lesson->name = (String)malloc(sizeof(char) * (strlen(data_ptr[i].lessons[count].name) + 1));
                strcpy_s(lesson->name, (strlen(data_ptr[i].lessons[count].name) + 1),
                         data_ptr[i].lessons[count].name);
                LessonNode lesson_node = {*lesson, NULL};
                AddLessonToList(&lesson_node, &student_set[i].lessons);
                count ++;
            }
            else
                break;
        }
        student_set[i].address = (String)malloc(sizeof(char) * (strlen(data_ptr[i].address) + 1));
        strcpy_s(student_set[i].address, strlen(data_ptr[i].address) + 1, data_ptr[i].address);
    }
    ReleaseStudentDataSetMemory(student_data_set);
    return student_set;
}

void ReleaseStudentDataSetMemory(Student_Data_Set* student_data)
{
    free(*student_data);
    *student_data = NULL;
    student_data = NULL;
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

Status RemoveStudent(unsigned long long id, StudentList* student_list)
{
    // get the head node
    StudentNode* student_ptr = *student_list;
    // compare the next node's id with it
    // if match, set the next node of the next node to this node's next
    // otherwise, let the pointer move to the next node
    // until the next node of the node which the pointer point to is null
    while (student_ptr->next != NULL)
    {
        if (student_ptr->next->data.id == id)
        {
            StudentNode* tmp_ptr = student_ptr->next;
            student_ptr->next = tmp_ptr->next;
            tmp_ptr->next = NULL;
            tmp_ptr = NULL;
            return OK;
        }
        student_ptr = student_ptr->next;
    }
    return EXCEPTION;
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

void AddLessonToList(LessonNode* lesson, LessonList* lesson_list)
{
    lesson->next = (*lesson_list)->next;
    (*lesson_list)->next = lesson;
}

int GetMaxId(StudentList student_list)
{
    unsigned long long max = NOT_ID;
    while (student_list->next != NULL)
    {
        // choose the bigger one between max and the id of next node and assign it to max
        max = student_list->next->data.id > max ? student_list->next->data.id : max;
        student_list = student_list->next;
    }
    return max;
}

LessonList CreateNewLessonList()
{
    LessonList lesson_list = (LessonList)malloc(sizeof(LessonNode));
    lesson_list->next = NULL;
    return lesson_list;
}

Student_Data_Set CreateStudentDataSet(int size)
{
    Student_Data_Set student_set = (Student_Data_Set)malloc(sizeof(Student_Data) * size);
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        while (count < 20)
        {
            student_set[i].lessons[count++].name[0] = '\0';
        }
    }
    return student_set;
}
