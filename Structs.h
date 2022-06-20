#pragma once

#ifndef STUDENT_MANAGEMENT_STRUCT_DEFINE

#define STUDENT_MANAGEMENT_STRUCT_DEFINE

// the class struct
typedef struct Lesson
{
    String name;
    float score;
}* LessonSet;

typedef struct LessonNode
{
    Lesson data;
    LessonNode* next;
}* LessonList;

// the student struct
typedef struct Student
{
    int id;
    String name;
    char sex;
    LessonList lessons;
    String address;
}* StudentSet;

typedef struct Lesson_Data
{
 char name[30];
 float score;
}* Lesson_Data_Set;

// the model use to save to or read from binary data
typedef struct Student_Data
{
    int id;
    char name[32];
    char sex;
    Lesson_Data lessons[20];
    char address[60];
}* Student_Data_Set;


// the student node
typedef struct StudentNode
{
    Student data;
    StudentNode* next;
}* StudentList;



#endif

#ifndef STUDENT_STRUCT_FUNCTION

#define STUDENT_STRUCT_FUNCTION

// the declarations about student struct

/**
 * \brief count the student number and return
 * \param student_list the student list
 * \return the number of student list
 */
int StudentCount(StudentList student_list);

/**
 * \brief write the student list data to binary object
 * \param student_list the student list
 * \return write status
 */
Status WriteStudent(StudentList student_list);

/**
 * \brief read the student list data from binary object and set it to the global variable
 */
StudentList* ReadStudent();

/**
 * \brief insert a student into the student list
 * \param student a new student
 * \param student_list the student list
 */
void AddStudentToList(StudentNode* student, StudentList* student_list);

/**
 * \brief find a student in the student list by id
 * \param id student id
 * \param student_list the student list
 * \return a student ptr to the student u want, but if there isn't data match, NULL will be return
 */
Student* GetStudent(int id, StudentList student_list);

/**
 * \brief init a new student node and return
 * \param student the data use to init this node
 * \return a new student Node
 */
StudentNode CreateNewStudentNode(Student student);

/**
 * \brief parse a ordinary data to data model, tips: this function will free the memory of the param students, don't use it after that
 * \param students the student set which will parse to data model, after this function running, this variable will be free
 * \return the parse result for ordinary data
 */
Student_Data_Set ParseToModel(StudentSet* students, int size);

/**
 * \brief release the memory of this student
 * \param student the student whose memory will be release
 */
void ReleaseStudentSetMemory(StudentSet* student);

/**
 * \brief parse the data read from binary data to ordinary data
 * \param student_data_set the data model include ordinary data
 * \param size the size of the data set
 * \return the student set
 */
StudentSet ParseToObject(Student_Data_Set student_data_set, int size);

/**
 * \brief release the memory of the student data set
 * \param student_data the data set whose memory will be release
 */
void ReleaseStudentDataSetMemory(Student_Data_Set*  student_data);
/**
 * \brief create a new student set and return
 * \param size declare the size of the new set
 * \return new student set
 */
StudentSet CreateStudentSet(int size);


/**
 * \brief create a new student data set and return
 * \param size declare the size of the new set
 * \return new student data set
 */
Student_Data_Set CreateStudentDataSet(int size);

// the declaration for Lesson struct

/**
 * \brief set a score by student's id and lesson name
 * \param student_id student id
 * \param lesson_name the name of the lesson
 * \param score the score
 */
void SetLessonScore(int student_id, String lesson_name, float score);

/**
 * \brief get someone score by the student's id and the lesson name
 * \param student_id student id
 * \param lesson_name the name of the lesson
 * \return the score
 */
float GetLessonScore(int student_id, String lesson_name);

/**
 * \brief create a new lesson list and return
 * \return a new lesson list
 */
LessonList CreateNewLessonList();

/**
 * \brief count the list and return the number
 * \param lesson_list the lesson list
 * \return the number of lessons
 */
int LessonCount(LessonList lesson_list);

#endif // !STUDENT_STRUCT_FUNCTION
