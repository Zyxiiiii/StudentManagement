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
        // id
        students[i].id = student_ptr->data.id;
        // name
        students[i].name = (String)malloc(sizeof(char) * (strlen(student_ptr->data.name) + 1));
        strcpy_s(students[i].name, strlen(student_ptr->data.name) + 1, student_ptr->data.name);
        // class
        students[i].clazz = (String)malloc(sizeof(char) * (strlen(student_ptr->data.clazz) + 1));
        strcpy_s(students[i].clazz, strlen(student_ptr->data.clazz) + 1, student_ptr->data.clazz);
        // sex
        students[i].sex = student_ptr->data.sex;
        // address
        students[i].address = (String)malloc(sizeof(char) * (strlen(student_ptr->data.address) + 1));
        strcpy_s(students[i].address, strlen(student_ptr->data.address) + 1, student_ptr->data.address);
        // lessons
        students[i].lessons = CreateNewLessonList();
        LessonNode* lesson_ptr = student_ptr->data.lessons;
        while (lesson_ptr->next != NULL)
        {
            LessonNode* lesson_node = (LessonNode*)malloc(sizeof(LessonNode));
            lesson_node->data.name = (String)malloc(sizeof(char) * (strlen(lesson_ptr->next->data.name) + 1));
            strcpy_s(lesson_node->data.name, strlen(lesson_ptr->next->data.name) + 1, lesson_ptr->next->data.name);
            lesson_node->data.score = lesson_ptr->next->data.score;
            lesson_node->next = NULL;
            AddLessonToList(lesson_node, &students[i].lessons);
            lesson_ptr = lesson_ptr->next;
        }


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
        if (students != NULL)
            ReleaseStudentSetMemory(&students, size);
        if (counter++ < 3)
            return WriteStudent(student_list);
        printf("\n\t\t\t数据写入失败，请重试");
        counter = 0;
        return ERROR;
    }
    if (students != NULL)
        ReleaseStudentSetMemory(&students, size);
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
            // create a new node and assign data to it
            StudentNode* student_node = (StudentNode*)malloc(sizeof(StudentNode));
            // id
            student_node->data.id = student_set->id;
            // name
            student_node->data.name = (String)malloc(sizeof(char) * (strlen(student_set->name) + 1));
            strcpy_s(student_node->data.name, strlen(student_set->name) + 1, student_set->name);
            // class
            student_node->data.clazz = (String)malloc(sizeof(char) * (strlen(student_set->clazz) + 1));
            strcpy_s(student_node->data.clazz, strlen(student_set->clazz) + 1, student_set->clazz);
            // lesson
            student_node->data.lessons = CreateNewLessonList();
            LessonList lesson_ptr = student_set->lessons->next;
            while (lesson_ptr != NULL)
            {
                LessonNode* new_lesson_node = (LessonNode*)malloc(sizeof(LessonNode));
                new_lesson_node->data.name = (String)malloc(sizeof(char) * (strlen(lesson_ptr->data.name) + 1));
                strcpy_s(new_lesson_node->data.name, strlen(lesson_ptr->data.name) + 1, lesson_ptr->data.name);
                new_lesson_node->data.score = lesson_ptr->data.score;
                new_lesson_node->next = NULL;
                AddLessonToList(new_lesson_node, &student_node->data.lessons);
                lesson_ptr = lesson_ptr->next;
            }
            // sex
            student_node->data.sex = student_set->sex;
            // address
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

Status SetLessonScore(Student* student, String lesson_name, float score)
{
    LessonNode* lesson_ptr = student->lessons->next;
    do
    {
        if (lesson_ptr != NULL && strcmp(lesson_ptr->data.name, lesson_name) == 0)
        {
            lesson_ptr->data.score = score;
            lesson_ptr = NULL;
            return OK;
        }
        lesson_ptr = lesson_ptr->next;
    }
    while (lesson_ptr != NULL);
    lesson_ptr = NULL;
    return EXCEPTION;
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
    StudentNode* work_ptr = *student_list;
    while (work_ptr->next != NULL)
    {
        if (work_ptr->next->data.id == id)
        {
            return &work_ptr->next->data;
        }
        work_ptr = work_ptr->next;
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
        LessonNode* lesson_ptr = student_ptr[i].lessons->next;
        while (count < 20)
        {
            if (lesson_ptr == NULL)
            {
                // if reach a null ptr, that means all the lesson after this index is null, so reset their data to avoid using a wrong memory 
                for (int j = count; j < 20; j++)
                {
                    student_data[i].lessons[j].name[0] = '\0';
                    student_data[i].lessons[j].score = -1.0;
                }
                break;
            }
            if (lesson_ptr->data.name[0] != '\0')
            {
                strcpy_s(student_data[i].lessons[count].name,
                         strlen(lesson_ptr->data.name) + 1,
                         lesson_ptr->data.name);
                student_data[i].lessons[count].score = lesson_ptr->data.score;
                count++;
                lesson_ptr = lesson_ptr->next;
            }
        }
        strcpy_s(student_data[i].address, strlen(student_ptr[i].address) + 1, student_ptr[i].address);
    }
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
            LessonNode* lesson_ptr = student_ptr->lessons;
            while (lesson_ptr->next != NULL)
            {
                if (lesson_ptr->next->data.name != NULL)
                {
                    free(lesson_ptr->next->data.name);
                    lesson_ptr->next->data.name = NULL;
                }
                lesson_ptr = lesson_ptr->next;
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
    StudentSet student_set = *CreateStudentSet(size);
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
                LessonNode* lesson_node = (LessonNode*)malloc(sizeof(LessonNode));
                lesson_node->data.name = (String)malloc(sizeof(char) * (strlen(data_ptr[i].lessons[count].name) + 1));
                strcpy_s((*lesson_node).data.name, (strlen(data_ptr[i].lessons[count].name) + 1),
                         data_ptr[i].lessons[count].name);
                lesson_node->data.score = data_ptr[i].lessons[count].score;
                AddLessonToList(lesson_node, &student_set[i].lessons);
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

StudentSet* CreateStudentSet(int size)
{
    StudentSet student_set = (StudentSet)malloc(sizeof(Student) * size);
    for (int i = 0; i < size; i++)
    {
        student_set->id = NOT_ID;
    }
    return &student_set;
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

void ShowStudent(Student student)
{
    printf("\n\n\t\t\t学号: %llu", student.id);
    printf("\n\t\t\t姓名: %s", student.name);
    printf("\n\t\t\t班别: %s", student.clazz);
    char sex[3];
    strcpy_s(sex, 3, student.sex == 'm' ? "男" : "女");
    printf("\n\t\t\t性别: %s", sex);
    printf("\n\t\t\t住址: %s", student.address);
    if (student.lessons->next == NULL)
    {
        printf("\n\t\t\t该学生当前没有课程\n");
    }
    else
    {
        printf("\n\t\t\t该学生当前的所有课程:");
        LessonNode* lesson_ptr = student.lessons;
        while (lesson_ptr->next != NULL)
        {
            printf("\n\t\t\t\t课程名: %s", lesson_ptr->next->data.name);
            printf("\n\t\t\t\t成绩: %.1f分", lesson_ptr->next->data.score < 0 ? 0 : lesson_ptr->next->data.score);
            lesson_ptr = lesson_ptr->next;
        }
    }
}

void ReleaseStudentListMemory(StudentList* student_list)
{
    StudentNode* student_ptr = *student_list;
    while (student_ptr != NULL)
    {
        if (student_ptr->data.address != NULL)
        {
            free(student_ptr->data.address);
            student_ptr->data.address = NULL;
        }
        if (student_ptr->data.name != NULL)
        {
            free(student_ptr->data.name);
            student_ptr->data.name = NULL;
        }
        if (student_ptr->data.lessons != NULL)
        {
            LessonNode* lesson_ptr = student_ptr->data.lessons->next;
            while (lesson_ptr != NULL)
            {
                if (lesson_ptr->data.name != NULL)
                {
                    free(lesson_ptr->data.name);
                    lesson_ptr->data.name = NULL;
                }
                lesson_ptr = lesson_ptr->next;
            }
        }
        if (student_ptr->data.clazz != NULL)
        {
            free(student_ptr->data.clazz);
            student_ptr->data.clazz = NULL;
        }
        student_ptr = student_ptr->next;
    }
    student_ptr = NULL;
}

void ReleaseRequestMemory(UpdateRequest* request)
{
    switch (request->dataType)
    {
    case NAME:
        if (request->data.str_data != NULL)
        {
            free(request->data.str_data);
            request->data.str_data = NULL;
        }
        break;
    case CLASS:
        if (request->data.str_data != NULL)
        {
            free(request->data.str_data);
            request->data.str_data = NULL;
        }
        break;
    case LESSON:
        if (request->data.lesson_data.name != NULL)
        {
            free(request->data.lesson_data.name);
            request->data.lesson_data.name = NULL;
        }
        break;
    case ADDRESS:
        if (request->data.str_data != NULL)
        {
            free(request->data.str_data);
            request->data.str_data = NULL;
        }
        break;
    }
}

void AddSortingNodeToList(SortLessonNode* sort_lesson_node, SortLessonList* sort_lesson_list)
{
    sort_lesson_node->next = (*sort_lesson_list)->next;
    (*sort_lesson_list)->next = sort_lesson_node;
}

void ShowSortingList(SortLessonList* sort_lesson_list, DisplayMode display_mode)
{
    // reverse or not
    if (display_mode == DESC)
    {
        ReverseTheSortingList(sort_lesson_list);
    }

    // display the list
    SortLessonNode* work_ptr = *sort_lesson_list;
    printf("\n\t\t\t学生名\t\t课程名\t\t分数");
    while (work_ptr->next != NULL)
    {
        printf("\n\n\t\t\t%s\t\t%s\t\t%.1f", work_ptr->next->student_name, work_ptr->next->lesson_name,
               work_ptr->next->score < 0 ? 0 : work_ptr->next->score);
        work_ptr = work_ptr->next;
    }

    printf("\n\n\t\t\t请输入命令以继续(1. 正序输出; 2. 倒序输出; 3. 统计; 4. 退出):");
    int order = GetOrderInput();
    while (order < 1 || order > 4)
    {
        order = GetOrderInput();
    }
    if (order != 4 && order != 3)
    {
        // if 'order' is equal to ASC(1), show this list in common again. Otherwise, reverse it and show again
        system("CLS");
        ShowSortingList(sort_lesson_list, order == ASC ? ASC : DESC);
    }
    if (order == 3)
    {
        DataController(sort_lesson_list);
    }

    // free the memory
    if (sort_lesson_list != NULL)
    {
        ReleaseTheSortingList(sort_lesson_list);
    }

    ScoreManagerWindow();
}

void ReverseTheSortingList(SortLessonList* sort_lesson_list)
{
    // init a new list, the size is the count of old list(because of it has head node, so its size must to plus one on original count)
    SortLessonList* reverse_sort_lesson_list = CreateNewSortingList();
    SortLessonNode* tmp_ptr;
    while ((*sort_lesson_list)->next != NULL)
    {
        // record the first effect node of the list as tmp_node
        tmp_ptr = (*sort_lesson_list)->next;
        // let the next node pointer of the head node of the original list point to the second node
        (*sort_lesson_list)->next = tmp_ptr->next;
        // the next node pointer of the tmp_node of the original list point to the first node of the new list
        tmp_ptr->next = (*reverse_sort_lesson_list)->next;
        // at last, the next node pointer of the head node of the new list point to 
        (*reverse_sort_lesson_list)->next = tmp_ptr;
    }
    (*sort_lesson_list)->next = (*reverse_sort_lesson_list)->next;
    (*reverse_sort_lesson_list)->next = NULL;
}

int CountTheSortingList(SortLessonList sort_lesson_list)
{
    int count = 0;
    SortLessonNode* sorting_ptr = sort_lesson_list->next;
    while (sorting_ptr != NULL)
    {
        count++;
        sorting_ptr = sorting_ptr->next;
    }
    return count;
}

SortLessonList* CreateNewSortingList()
{
    SortLessonList sort_lesson_list = (SortLessonList)malloc(sizeof(SortLessonNode));
    sort_lesson_list->next = NULL;
    sort_lesson_list->student_name = NULL;
    sort_lesson_list->lesson_name = NULL;
    sort_lesson_list->score = -1;
    return &sort_lesson_list;
}

SortLessonNode* CreateNewSortingNode()
{
    SortLessonNode* sort_lesson_node = (SortLessonNode*)malloc(sizeof(SortLessonNode));
    sort_lesson_node->score = -1.0;
    sort_lesson_node->next = NULL;
    return sort_lesson_node;
}

void ReleaseTheSortingList(SortLessonList* sort_lesson_list)
{
    if (*sort_lesson_list != NULL)
    {
        SortLessonNode* work_ptr = (*sort_lesson_list)->next;
        while (work_ptr != NULL)
        {
            if (work_ptr->student_name != NULL)
            {
                free(work_ptr->student_name);
                work_ptr->student_name = NULL;
            }
            if (work_ptr->lesson_name != NULL)
            {
                free(work_ptr->lesson_name);
                work_ptr->lesson_name = NULL;
            }
            work_ptr = work_ptr->next;
        }
        free(*sort_lesson_list);
        *sort_lesson_list = NULL;
    }
}

SortLessonList* ParseToSortingList(StudentList* student_list)
{
    StudentNode* student_ptr = *student_list;

    SortLessonList sort_lesson_list = *CreateNewSortingList();
    while (student_ptr->next != NULL)
    {
        if (student_ptr->next->data.lessons->next != NULL)
        {
            LessonNode* lesson_ptr = student_ptr->next->data.lessons;
            while (lesson_ptr->next != NULL)
            {
                // package the data into the sorting list
                SortLessonNode* sorting_node = CreateNewSortingNode();
                sorting_node->lesson_name = (String)malloc(sizeof(char) * (strlen(lesson_ptr->next->data.name) + 1));
                sorting_node->student_name = (String)malloc(sizeof(char) * (strlen(student_ptr->next->data.name) + 1));
                strcpy_s(sorting_node->student_name, strlen(student_ptr->next->data.name) + 1,
                         student_ptr->next->data.name);
                strcpy_s(sorting_node->lesson_name, strlen(lesson_ptr->next->data.name) + 1,
                         lesson_ptr->next->data.name);
                sorting_node->score = lesson_ptr->next->data.score;
                AddSortingNodeToList(sorting_node, &sort_lesson_list);
                lesson_ptr = lesson_ptr->next;
            }
        }
        student_ptr = student_ptr->next;
    }
    if (student_list != NULL)
    {
        ReleaseStudentListMemory(student_list);
    }
    return &sort_lesson_list;
}

float SortAverage(SortLessonList sort_lesson_list)
{
    int count = 0;
    float sum = 0;
    while (sort_lesson_list->next != NULL)
    {
        sum += sort_lesson_list->next->score < 0 ? 0 : sort_lesson_list->next->score;
        count ++;
        sort_lesson_list = sort_lesson_list->next;
    }
    return sum / count;
}

float SortExcellentRate(SortLessonList sort_lesson_list)
{
    int excellent = 0;
    int count = 0;
    while (sort_lesson_list->next != NULL)
    {
        count++;
        if (sort_lesson_list->next->score > 90)
        {
            excellent++;
        }
        sort_lesson_list = sort_lesson_list->next;
    }
    return 1.0 * excellent / count;
}

float SortPassRate(SortLessonList sort_lesson_list)
{
    int count = 0;
    int pass = 0;
    while (sort_lesson_list->next != NULL)
    {
        count++;
        if (sort_lesson_list->next->score > 60.0)
        {
            pass++;
        }
        sort_lesson_list = sort_lesson_list->next;
    }
    return 1.0 * pass / count;
}

void ShowTheFailList(SortLessonList sort_lesson_list)
{
    printf("\n\n\t\t\t以下为成绩不及格的课程及学生名单:");
    while (sort_lesson_list->next != NULL)
    {
        if (sort_lesson_list->next->score < 60.0)
        {
            printf("\n\n\t\t\t姓名：%s;\n\t\t\t课程名： %s;\n\t\t\t成绩：%.1f分", sort_lesson_list->next->student_name, sort_lesson_list->next->lesson_name,
                   sort_lesson_list->next->score < 0 ? 0 : sort_lesson_list->next->score);
        }
        sort_lesson_list = sort_lesson_list->next;
    }
    printf("\n\n\t\t\t");
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
    lesson_list->data.name = NULL;
    lesson_list->data.score = -1.0;
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
