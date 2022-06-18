#include"AllHeader.h"

#define HEADER "欢迎使用学生成绩管理系统"
#define FOOTER "退出系统"

// 主窗体
void MainWindow(String body[], int lines);

void MainWindow(String body[], int lines)
{
    system("CLS");

    printf("\n\n%s\n\n", &HEADER);

    for (int i = 0; i < lines; i++)
    {
        printf("%d. %s\n\n", i + 1, body[i]);
    }

    printf("%d. 退出\n\n", lines + 1);

    printf("请输入相应的命令:");

    free(body);
}

void IndexWindow()
{
    String* body = (String*)malloc(sizeof(String) * 2);

    // assign value to body
    body[0] = (String)malloc(sizeof(String));
    strcpy_s(*(body), 20, "学生信息管理系统");
    body[1] = (String)malloc(sizeof(String));
    strcpy_s(*(body + 1), 20, "学生成绩管理系统");

    MainWindow(body, 2);

    StartController();
}
