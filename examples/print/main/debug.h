#ifndef __DEBUG_H_
#define __DEBUG_H_

#include <stdio.h>
#include <stdarg.h>
#include "misc.h"

#define BUF_SIZE (1024)

void initDEBUG(uint32_t baudrate);
void putcharDEBUG(uint8_t data);
void printDEBUG(char * str, ... );
void sprintDEBUG(uint8_t * str);

#endif 
