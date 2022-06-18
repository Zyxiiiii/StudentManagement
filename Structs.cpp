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


Status WriteStudent(StudentList studentList)
{
	// ensure it will begin at head node
	studentList = studentList->head;
	int size = StudentCount(studentList);
	StudentSet students = (StudentSet)malloc(size * sizeof(Student));
	// package them to a set
	for (int i = 0; i < size; i++)
	{
		*(students + size) = studentList->data;
		ToNextNode(studentList);
	}
	// start writing
	FILE* file = fopen(STUDENT_BINARY_OBJ, "wb");
	fwrite(students, sizeof(Student), size, file);
	fclose(file);
	return OK;
}

StudentList ReadStudent()
{
	FILE * file = fopen(STUDENT_BINARY_OBJ, "rb");
	
	// move the file ptr point to the end of the file,
	// and get it position to know the size of this file,
	// than could get the size of the student through the file's size divide by the student's size at last
	fseek(file, 0L, SEEK_END);
	int size = ftell(file) / sizeof(Student);
	StudentSet students = (StudentSet) malloc(sizeof(Student) * size);

	StudentList studentList;
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


void SetClassScore(Student* student, String className, float score)
{
	ClassList classList = student->classes;
	if (className == classList->name)
	{
		classList->score = score;
		return;
	}
	printf("没有找到[%s]这门课噢!", className);
}

float GetClassScore(Student* student, String className)
{
	ClassList classList = student->classes;
	if (className == classList->name)
	{
		return classList->score;
	}
	printf("没有找到[%s]这门课噢!", className);
	return -1;
}


void ToNextNode(StudentNode* student)
{
	student->data = student->next->data;
	student->next = student->next->next;
}

int StudentCount(StudentList studentList) {
	int count = 1;

	studentList = studentList->head;

	while (studentList->next != NULL)
	{
		ToNextNode(studentList);
	}

	return count;
}

void InitStudentList(StudentList studentList) {
	studentList->head = studentList;
	studentList->next = NULL;
}

void AddStudentToList(StudentNode * student, StudentList studentList)
{
	// 头插法
	student->next = studentList->head;
	studentList->head = student;
}

Student* GetStudent(int id, StudentList studentList)
{
	while (studentList->next != NULL)
	{
		if (studentList->data.id == id)
		{
			return &studentList->data;
		}
	}

	printf("没有找到id为:%d的学生", &id);

	return NULL;
}
