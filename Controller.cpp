#include "AllHeader.h"

void IndexController()
{
    switch (GetOrderInput())
    {
    case 1:
        StudentInfoWindow();
        break;
    case 2:
        ScoreManagerWindow();
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
        SearchScoreByStudent();
        break;
    case 3:
        SearchScoreByLesson();
        break;
    case 4:
        UpdateStudentScore();
        break;
    case 5:
        AddLessonForStudent();
        break;
    case 6:
        IndexWindow();
        break;
    default:
        printf("\t\t\t请输入正确的命令:");
        ScoreManagerController();
    }
}

void DataController(const SortLessonList* sort_lesson_list)
{
    printf("\n\t\t\t1. 求平均值");
    printf("\n\t\t\t2. 求优秀率");
    printf("\n\t\t\t3. 求某一科大于某分数的所有同学");
    printf("\n\t\t\t4. 按总成绩由大到小排序");
    printf("\n\t\t\t5. 按总成绩由小到大排序");
    printf("\n\t\t\t6. 退出");
    printf("\n\n\t\t\t请选择您的操作:");
    switch (GetOrderInput())
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        return ScoreManagerWindow();
    default:
        printf("\t\t\t请输入正确的命令:");
    }
    DataController(sort_lesson_list);
}
