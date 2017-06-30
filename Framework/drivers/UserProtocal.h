#ifndef __PROTOCAL_H
#define	__PROTOCAL_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned char u8;

u8 ComProtocal(char*rxbuf,char*head,char*end,char* separater,char dataout[][15]);


#endif

