#include"AllHeader.h"

#define HEADER "��ӭʹ��ѧ���ɼ�����ϵͳ"
#define FOOTER "�˳�ϵͳ"

// ������
void MainWindow(String *body, int lines);

void MainWindow(String *body, int lines)
{
    system("CLS");

    printf("\n\n\t\t\t\t\t\t%s\n\n", &HEADER);

    for (int i = 0; i < lines; i++)
    {
        printf("\t\t\t%d. %s\n\n", i + 1, *(body + i));
    }

    printf("\t\t\t%d. �˳�\n\n", lines + 1);

    printf("\t\t\t��������Ӧ������:");
    
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
    String* body = InitStringList(5);

    // assign value to body
    strcpy_s(*(body), 20, "����ѧ��");
    strcpy_s(*(body + 1), 20, "ɾ��ѧ��");
    strcpy_s(*(body + 2), 20, "��ѯѧ����Ϣ");
    strcpy_s(*(body + 3), 20, "�޸�ѧ����Ϣ");
    strcpy_s(*(body + 4), 20, "�鿴����ѧ����Ϣ");

    MainWindow(body, 5);

    StudentInfoController();
}

void ScoreManagerWindow()
{
    String* body = InitStringList(5);

    // assign value to body
    strcpy_s(*(body), 20, "��ѯ����ѧ���ĳɼ�");
    strcpy_s(*(body + 1), 20, "��ѯ��һѧ���ĳɼ�");
    strcpy_s(*(body + 2), 30, "��ѯ��һ��Ŀ������ѧ���ɼ�");
    strcpy_s(*(body + 3), 20, "�޸�ѧ���ɼ�");
    strcpy_s(*(body + 4), 20, "��ӿγ�");

    MainWindow(body, 5);

    ScoreManagerController();
}
