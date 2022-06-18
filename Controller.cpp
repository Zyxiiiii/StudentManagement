#include <iso646.h>

#include "AllHeader.h"

#ifndef CONTROLLER_DEF

#define CONSTANT_DEF

/**
 * \brief control the client input will give a meaningful value
 * \return client input
 */
int GetOrderInput();

#endif


void StartController()
{
    switch (GetOrderInput())
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        exit(0);
    default:
        printf("请输入正确的命令:");
        StartController();
    }
}

int GetOrderInput()
{
    String origin_input = (String) malloc(sizeof(String));
    scanf_s("%s", origin_input);
    char order_position = origin_input[0];
    if (order_position >= '0' && order_position < '9')
    {
        free(origin_input);
        return (int) order_position - '0';
    }
    printf("请输入正确的命令:");
    free(origin_input);
    GetOrderInput();
}
