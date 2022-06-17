#include "AllHeader.h"

// ����
void stu_foreach(StudentList studentList, bool(* func)(Student*)) {
	for (int i = 0; i < stu_count(studentList); i++) {
		if (!(*func)(&studentList->data)) {
			printf("stu_foreach�����ڴ���%dʱ�������쳣", studentList->data.stuNum);
			nextNode(&studentList);
		}
	}
}

int stu_count(StudentList studentList) {
	int first = studentList->data.stuNum;
	int count = 0;
	while (studentList->data.stuNum != first) {
		count++;
		nextNode(&studentList);
	}
	return count;
}

void nextNode(StudentList *studentList) {
	(*studentList)->prior = *studentList;
	(*studentList)->data = (*studentList)->next->data;
	(*studentList)->next = (*studentList)->next->next;
}

void lastNode(StudentList* studentList) {
	(*studentList)->next = *studentList;
	(*studentList)->data = (*studentList)->prior->data;
	(*studentList)->prior = (*studentList)->prior->prior;
}
