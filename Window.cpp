#include"AllHeader.h"

#define HEADER "��ӭʹ��ѧ���ɼ�����ϵͳ"
#define FOOTER "�˳�ϵͳ"

// ������
void MainWindow(String *body, int lines);

void MainWindow(String *body, int lines)
{
    system("CLS");

    printf("\n\n%s\n\n", &HEADER);

    for (int i = 0; i < lines; i++)
    {
        printf("%d. %s\n\n", i + 1, *(body + i));
    }

    printf("%d. �˳�\n\n", lines + 1);

    printf("��������Ӧ������:");
    
    FreeStringList(body, lines);
}

void IndexWindow()
{
    String* body = InitStringList(2);
    

    // assign value to body
    strcpy_s(*body, 20, "ѧ����Ϣ����ϵͳ");
    strcpy_s(*(body+ 1), 20, "ѧ���ɼ�����ϵͳ");

    MainWindow(body, 2);

    IndexController();
}

void StudentInfoWindow()
{
    String* body = InitStringList(4);

    // assign value to body
    strcpy_s(*(body), 20, "����ѧ��");
    strcpy_s(*(body + 1), 20, "ɾ��ѧ��");
    strcpy_s(*(body + 2), 20, "��ѯѧ����Ϣ");
    strcpy_s(*(body + 3), 20, "�޸�ѧ����Ϣ");

    MainWindow(body, 4);

    StudentInfoController();
}
