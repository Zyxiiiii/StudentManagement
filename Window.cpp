#include"AllHeader.h"

#define HEADER "欢迎使用学生成绩管理系统"
#define FOOTER "退出系统"

// 主窗体
void mainWindow(String body[], int lines);

void mainWindow(String body[], int lines)
{
	system("CLS");

	printf("\n\n%s\n\n", &HEADER);

	for (int i = 0; i < lines; i++)
	{
		printf("%d. %s\n\n", i + 1, body[i]);
	}

	printf("%d. 退出\n\n", lines);

	printf("请输入相应的命令:");
}
