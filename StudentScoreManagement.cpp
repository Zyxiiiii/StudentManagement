#include "AllHeader.h"

int main(int argc, char** argv)
{
    IndexWindow();

    system("pause");

    return 0;
}

String* InitStringList(int length)
{
    // give the string list memory that the memory size of it is length
    String* string_list = (String*)malloc(sizeof(String) * length);
    for (int i = 0; i < length; i++)
    {
        // malloc each string ptr
        *(string_list + i) = (String)malloc(sizeof(char) * 20);
    }
    return string_list;
}

void FreeStringList(String* string_list, int length)
{
    // free the memory of each index of the list
    for (int i = 0; i < length; i++)
    {
        free(*(string_list + i));
        *(string_list + i) = NULL;
    }

    // free the memory of the list
    free(string_list);
    string_list = NULL;
}

int GetOrderInput()
{
    String origin_input = (String)malloc(sizeof(char) * 2);
    scanf_s("%s", origin_input, 2);
    // compare origin_input with "" can know the size of client input is out of index or not
    char order = origin_input[0];
    if (strcmp(origin_input, "") != 0 && (order >= '0' && order < '9'))
    {
        free(origin_input);
        origin_input = NULL;
        return (int)order - '0';
    }
    printf("\t\t\t请输入正确的命令:");
    free(origin_input);
    origin_input = NULL;
    GetOrderInput();
}
