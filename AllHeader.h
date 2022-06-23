#pragma once

#ifndef STRING_DEF

#define STRING_DEF	

typedef char* String;

/**
 * \brief init a new string list and return
 * \param length the size of the string list
 * \return the string which has initialized
 */
String* InitStringList(int length);

/**
 * \brief free the memory size of a list
 * \param string_list the string list is waiting for free
 * \param length the length of the list
 */
void FreeStringList(String* string_list, int length);

#endif // !STRING


#ifndef CONSTANT_DEF

#define CONSTANT_DEF

typedef int Status;

typedef int Bool;

#define OK 0

#define ERROR (-1)

#define EXCEPTION 1

#define NOT_ID (0)

#define MAN 'm'

#define WOMEN 'f'

#define TRUE 1

#define FALSE 0

#endif // !CONSTANT_DEF

#ifndef INPUT_DEF

#define INPUT_DEF

/**
 * \brief control the client input will give a meaningful value
 * \return client input
 */
int GetOrderInput();

#endif


// header
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include<math.h>
#include<malloc.h>
#include"Structs.h"
#include"Window.h"
#include"Controller.h"
#include "Service.h"
