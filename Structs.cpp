#include "AllHeader.h"

// ˽������

#define STUDENT_BINARY_OBJ "./student.obj"

#ifndef STUDENT_PRIVATE_DEF

#define STUDENT_PRIVATE_DEF

// �ƶ�����һ���
void ToNextNode(StudentNode* student);

// ��ʼ��ѧ������
void InitStudentList(StudentList);


#endif // !STUDENT_PRIVATE_DEF


Status WriteStudent(StudentList studentList)
{
	// ȷ����ͷ��ʼ
	studentList = studentList->head;
	int size = StudentCount(studentList);
	StudentSet students = (StudentSet)malloc(size * sizeof(Student));
	// ��װ�ɼ���
	for (int i = 0; i < size; i++)
	{
		*(students + size) = studentList->data;
		ToNextNode(studentList);
	}
	// ��ʼд��
	FILE* file = fopen(STUDENT_BINARY_OBJ, "wb");
	fwrite(students, sizeof(Student), size, file);
	fclose(file);
}

StudentList ReadStudent()
{
	FILE * file = fopen(STUDENT_BINARY_OBJ, "rb");
	
	// ��file�����ļ�ĩβ��������ǰ��λ�á������ļ�ռ���ֽ���������Student��ռ���ֽڴ�С�����ɵ�֪�ж��ٸ�����
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

	// �ص�����
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
	printf("û���ҵ�[%s]���ſ���!", className);
}

float GetClassScore(Student* student, String className)
{
	ClassList classList = student->classes;
	if (className == classList->name)
	{
		return classList->score;
	}
	printf("û���ҵ�[%s]���ſ���!", className);
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
	// ͷ�巨
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

	printf("û���ҵ�idΪ:%d��ѧ��", &id);

	return NULL;
}
