#include "AllHeader.h"

// 私有声明

#define STUDENT_BINARY_OBJ "./student.obj"

#ifndef STUDENT_PRIVATE_DEF

#define STUDENT_PRIVATE_DEF

// 移动到下一结点
void ToNextNode(StudentNode* student);

// 初始化学生链表
void InitStudentList(StudentList);


#endif // !STUDENT_PRIVATE_DEF


Status WriteStudent(StudentList studentList)
{
	// 确保从头开始
	studentList = studentList->head;
	int size = StudentCount(studentList);
	StudentSet students = (StudentSet)malloc(size * sizeof(Student));
	// 包装成集合
	for (int i = 0; i < size; i++)
	{
		*(students + size) = studentList->data;
		ToNextNode(studentList);
	}
	// 开始写入
	FILE* file = fopen(STUDENT_BINARY_OBJ, "wb");
	fwrite(students, sizeof(Student), size, file);
	fclose(file);
}

StudentList ReadStudent()
{
	FILE * file = fopen(STUDENT_BINARY_OBJ, "rb");
	
	// 将file置于文件末尾，读出当前的位置——即文件占的字节数，除以Student所占的字节大小，即可得知有多少个对象
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
