#include"AllHeader.h"

#define HEADER "欢迎使用学生成绩管理系统"
#define FOOTER "退出系统"

// 主窗体
void MainWindow(String *body, int lines);

void MainWindow(String *body, int lines)
{
    system("CLS");

    printf("\n\n%s\n\n", &HEADER);

    for (int i = 0; i < lines; i++)
    {
        printf("%d. %s\n\n", i + 1, *(body + i));
    }

    printf("%d. 退出\n\n", lines + 1);

    printf("请输入相应的命令:");
    
    FreeStringList(body, lines);
}

void IndexWindow()
{
    String* body = InitStringList(2);
    

    // assign value to body
    strcpy_s(*body, 20, "学生信息管理系统");
    strcpy_s(*(body+ 1), 20, "学生成绩管理系统");

    MainWindow(body, 2);

    IndexController();
}

void StudentInfoWindow()
{
    String* body = InitStringList(4);

    // assign value to body
    strcpy_s(*(body), 20, "新增学生");
    strcpy_s(*(body + 1), 20, "删除学生");
    strcpy_s(*(body + 2), 20, "查询学生信息");
    strcpy_s(*(body + 3), 20, "修改学生信息");

    MainWindow(body, 4);

    StudentInfoController();
}
