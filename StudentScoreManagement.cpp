#include "AllHeader.h"

int main(int argc, char** argv)
{
    IndexWindow();

    getchar();

    system("pause");

    return 0;
}

String* InitStringList(int length)
{
    // give the string list memory that the memory size of it is length
    String* string_list = (String*) malloc(sizeof(String) * length);
    for (int i = 0; i < length; i++)
    {
        // malloc each string ptr
        *(string_list + i) = (String) malloc(sizeof(char) * 20);
    }
    return string_list;
}

void FreeStringList(String* string_list, int length)
{
    // free the memory of each index of the list
    for (int i = 0; i < length; i++)
    {
        free(*(string_list + i));
    }

    // free the memory of the list
    free(string_list);
}
