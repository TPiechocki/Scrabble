//
// Created by Tomasz Piechocki on 23/11/2018.
//

#include"../conio2.h"
#include "core.h"

#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC    extern "C"
#else
#define EXTERNC
#endif


EXTERNC
int boardXPosition(int conPos) {
    return conPos - BOARD_POSITION - BOARD_PADDING;
}

EXTERNC
int boardYPosition(int conPos) {
    return conPos - BOARD_PADDING;
}

EXTERNC
void error(const char *info) {
    clrscr();
    gotoxy(10,10);
    cputs(info);
    getch();
}
