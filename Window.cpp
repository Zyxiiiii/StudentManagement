#include"AllHeader.h"

#define HEADER "��ӭʹ��ѧ���ɼ�����ϵͳ"
#define FOOTER "�˳�ϵͳ"

// ������
void mainWindow(String body[], int lines);

void mainWindow(String body[], int lines)
{
	system("CLS");

	printf("\n\n%s\n\n", &HEADER);

	for (int i = 0; i < lines; i++)
	{
		printf("%d. %s\n\n", i + 1, body[i]);
	}

	printf("%d. �˳�\n\n", lines);

	printf("��������Ӧ������:");
}
