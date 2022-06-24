#include "AllHeader.h"

void IndexController()
{
    switch (GetOrderInput())
    {
    case 1:
        StudentInfoWindow();
        break;
    case 2:
        break;
    case 3:
        exit(0);
    default:
        printf("\t\t\t请输入正确的命令:");
        IndexController();
    }
}

void StudentInfoController()
{
    switch (GetOrderInput())
    {
    case 1:
        AddStudent();
        break;
    case 2:
        DeleteStudent();
        break;
    case 3:
        SearchStudent();
        break;
    case 4:
        UpdateStudentInfo();
        break;
    case 5:
        ShowAllStudent();
        break;
    case 6:
        IndexWindow();
        break;
    default:
        printf("\t\t\t请输入正确的命令:");
        StudentInfoController();
    }
}

void ScoreManagerController()
{
    switch (GetOrderInput())
    {
    case 1:
        SearchAllScore();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        IndexController();
        break;
    default:
        printf("\t\t\t请输入正确的命令:");
        ScoreManagerController();
    }
}
