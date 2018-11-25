//
// Created by Tomasz Piechocki on 23/11/2018.
//

#include<stdio.h>
#include"../conio2.h"
#include "core.h"

#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

const int AMOUNT_ALL_LETTERS = AMOUNT_OF_A + AMOUNT_OF_B + AMOUNT_OF_C + AMOUNT_OF_D + AMOUNT_OF_E +
        AMOUNT_OF_F + AMOUNT_OF_F + AMOUNT_OF_G + AMOUNT_OF_H + AMOUNT_OF_I + AMOUNT_OF_J +
        AMOUNT_OF_K + AMOUNT_OF_L + AMOUNT_OF_M + AMOUNT_OF_N + AMOUNT_OF_O + AMOUNT_OF_P +
        AMOUNT_OF_Q + AMOUNT_OF_R + AMOUNT_OF_S + AMOUNT_OF_T + AMOUNT_OF_U + AMOUNT_OF_V +
        AMOUNT_OF_W + AMOUNT_OF_X + AMOUNT_OF_Y + AMOUNT_OF_Z + AMOUNT_OF_BLANK;

EXTERNC
int readArrow(int ch) {
    switch (ch) {           // this is an arrow
        case 0x48:
            return UP;
        case 0x50:
            return DOWN;
        case 0x4b:
            return LEFT;
        case 0x4d:
            return RIGHT;
        default:
            return 0;
    }
}

EXTERNC
void moveCursor(board_status_t *board, int dir) {
    switch (dir) {           // this is an arrow
        case UP:
            (board->yBoard > 1) ? board->y-- : NULL;
            break;
        case DOWN:
            (board->yBoard < BOARD_SIZE) ? board->y++ : NULL;
            break;
        case LEFT:
            (board->xBoard > 1) ? board->x-- : NULL;
            break;
        case RIGHT:
            (board->xBoard < BOARD_SIZE) ? board->x++ : NULL;
            break;
        default:
            break;
    }
    boardPosition(board);
}


EXTERNC
void boardPosition(board_status_t *board) {
    board->xBoard = board->x - BOARD_POSITION - BOARD_PADDING;
    board->yBoard = board->y - BOARD_PADDING;
}

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
    cputs("Error: ");
    cputs(info);
    gotoxy(10,12);
    cputs("Press Enter to close this message.");
    int quit;
    do {
        quit = getch();
    } while (quit != 0x0d);
    clrscr();
}

EXTERNC
char toUpper(char letter) {
    if ((letter >= 'A' && letter <= 'Z') || letter == 0x0d || letter == 0x1b)
        return letter;
    else if (letter >= 'a' && letter <= 'z')
        return letter - ('a' - 'A');
    else
        return 1;
}
