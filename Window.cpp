#include"AllHeader.h"

#define HEADER "��ӭʹ��ѧ���ɼ�����ϵͳ"
#define FOOTER "�˳�ϵͳ"

// ������
void MainWindow(String body[], int lines);

void MainWindow(String body[], int lines)
{
    system("CLS");

    printf("\n\n%s\n\n", &HEADER);

    for (int i = 0; i < lines; i++)
    {
        printf("%d. %s\n\n", i + 1, body[i]);
    }

    printf("%d. �˳�\n\n", lines + 1);

    printf("��������Ӧ������:");

    free(body);
}

void IndexWindow()
{
    String* body = (String*)malloc(sizeof(String) * 2);

    // assign value to body
    body[0] = (String)malloc(sizeof(String));
    strcpy_s(*(body), 20, "ѧ����Ϣ����ϵͳ");
    body[1] = (String)malloc(sizeof(String));
    strcpy_s(*(body + 1), 20, "ѧ���ɼ�����ϵͳ");

    MainWindow(body, 2);

    StartController();
}
