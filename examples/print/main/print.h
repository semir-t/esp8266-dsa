#ifndef __PRINT_H_
#define __PRINT_H_

#include <stdio.h>
#include <stdarg.h>
#include "misc.h"

#define BUF_SIZE (1024)

void initPRINT(uint32_t baudrate);
void putcharPRINT(uint8_t data);
void printPRINT(char * str, ... );
void sprintPRINT(uint8_t * str);

#endif 
