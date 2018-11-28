//
// Created by Tomasz Piechocki on 23/11/2018.
//

#include<stdio.h>
#include<stdlib.h>
#include"time.h"
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

// fill next pool tiles from count position with amount of particular letter
void fillWithLetter(char pool[], int amount, char letter, int *count) {
    for (int i = 0; i < amount; ++i) {
        pool[*count] = letter;
        (*count)++;
    }
}
// fill pool in alphabetical order
void fillPool(char pool[]) {
    int count = 0;
    fillWithLetter(pool, AMOUNT_OF_A, 'A', &count);
    fillWithLetter(pool, AMOUNT_OF_B, 'B', &count);
    fillWithLetter(pool, AMOUNT_OF_C, 'C', &count);
    fillWithLetter(pool, AMOUNT_OF_D, 'D', &count);
    fillWithLetter(pool, AMOUNT_OF_E, 'E', &count);
    fillWithLetter(pool, AMOUNT_OF_F, 'F', &count);
    fillWithLetter(pool, AMOUNT_OF_G, 'G', &count);
    fillWithLetter(pool, AMOUNT_OF_H, 'H', &count);
    fillWithLetter(pool, AMOUNT_OF_I, 'I', &count);
    fillWithLetter(pool, AMOUNT_OF_J, 'J', &count);
    fillWithLetter(pool, AMOUNT_OF_K, 'K', &count);
    fillWithLetter(pool, AMOUNT_OF_L, 'L', &count);
    fillWithLetter(pool, AMOUNT_OF_M, 'M', &count);
    fillWithLetter(pool, AMOUNT_OF_N, 'N', &count);
    fillWithLetter(pool, AMOUNT_OF_O, 'O', &count);
    fillWithLetter(pool, AMOUNT_OF_P, 'P', &count);
    fillWithLetter(pool, AMOUNT_OF_Q, 'Q', &count);
    fillWithLetter(pool, AMOUNT_OF_R, 'R', &count);
    fillWithLetter(pool, AMOUNT_OF_S, 'S', &count);
    fillWithLetter(pool, AMOUNT_OF_T, 'T', &count);
    fillWithLetter(pool, AMOUNT_OF_U, 'U', &count);
    fillWithLetter(pool, AMOUNT_OF_V, 'V', &count);
    fillWithLetter(pool, AMOUNT_OF_W, 'W', &count);
    fillWithLetter(pool, AMOUNT_OF_X, 'X', &count);
    fillWithLetter(pool, AMOUNT_OF_Y, 'Y', &count);
    fillWithLetter(pool, AMOUNT_OF_Z, 'Z', &count);
    fillWithLetter(pool, AMOUNT_OF_BLANK, BLANK, &count);
}
// swap two elements with indexes i and index
void swapPoolElements(char pool[], int i, int index) {
    char temp;
    temp = pool[i];
    pool[i] = pool[index];
    pool[index] = temp;
}
// make the pool order random
void randomizePool(char pool[]) {
    srand((unsigned int)time(NULL));
    int index;
    for (int i = 0; i < AMOUNT_ALL_LETTERS; ++i) {
        index = rand() % AMOUNT_ALL_LETTERS;
        swapPoolElements(pool, i, index);
    }
}

EXTERNC
void swapChars(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

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

EXTERNC
void createPool(char pool[]) {
    fillPool(pool);         // fill with proper amount of every letter
    randomizePool(pool);    // randomize letters inside the array
}
