//
// Created by Tomasz Piechocki on 23/11/2018.
//

#include<stdio.h>
#include<stdlib.h>
#include"time.h"
#include"../conio2.h"
#include"core.h"
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
// make the pool order random
void randomizePool(char pool[]) {
    srand((unsigned int)time(NULL));
    for (int i = 0, index; i < AMOUNT_ALL_LETTERS; ++i) {
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
char *toLowerWord(char *word) {
    for (int i = 0; word[i] != '\0' ; ++i) {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] = word[i] - ('A'-'a');
    }
    return word;
}

EXTERNC
void createPool(char pool[]) {
    fillPool(pool);         // fill with proper amount of every letter
    randomizePool(pool);    // randomize letters inside the array
}

EXTERNC
void swapPoolElements(char pool[], int i, int index) {
    char temp;
    temp = pool[i];
    pool[i] = pool[index];
    pool[index] = temp;
}

// negative numbers for word bonus and positive for letter bonus
const short bonus_tiles[][3] = {
        // middle tile
        {-2, MIDDLE_TILE, MIDDLE_TILE},
        // 3x word
        {-3, 1, 1},
        {-3, BOARD_SIZE, BOARD_SIZE},
        {-3, 1, BOARD_SIZE},
        {-3, BOARD_SIZE, 1},
        {-3, MIDDLE_TILE, 1},
        {-3, MIDDLE_TILE, BOARD_SIZE},
        {-3, 1, MIDDLE_TILE},
        {-3, BOARD_SIZE, MIDDLE_TILE},
        // 2x word
        {-2, 2, 2},             // left half
        {-2, 2, BOARD_SIZE-1},
        {-2, 3, 3},
        {-2, 3, BOARD_SIZE-2},
        {-2, 4, 4},
        {-2, 4, BOARD_SIZE-3},
        {-2, 5, 5},
        {-2, 5, BOARD_SIZE-4},
        {-2, BOARD_SIZE-1, 2},  // right half
        {-2, BOARD_SIZE-1, BOARD_SIZE-1},
        {-2, BOARD_SIZE-2, 3},
        {-2, BOARD_SIZE-2, BOARD_SIZE-2},
        {-2, BOARD_SIZE-3, 4},
        {-2, BOARD_SIZE-3, BOARD_SIZE-3},
        {-2, BOARD_SIZE-4, 5},
        {-2, BOARD_SIZE-4, BOARD_SIZE-4},
        // 3x letter
        {3, MIDDLE_TILE-2, 2},
        {3, MIDDLE_TILE+2, 2},
        {3, MIDDLE_TILE-2, BOARD_SIZE-1},
        {3, MIDDLE_TILE+2, BOARD_SIZE-1},
        {3, 2, MIDDLE_TILE-2},
        {3, 2, MIDDLE_TILE+2},
        {3, BOARD_SIZE-1, MIDDLE_TILE-2},
        {3, BOARD_SIZE-1, MIDDLE_TILE+2},
        {3, MIDDLE_TILE-2, MIDDLE_TILE-2}, // around middle
        {3, MIDDLE_TILE-2, MIDDLE_TILE+2},
        {3, MIDDLE_TILE+2, MIDDLE_TILE-2},
        {3, MIDDLE_TILE+2, MIDDLE_TILE+2},
        // 2x letter
        {2, MIDDLE_TILE-BOARD_SIZE/4-1, 1},     // next to border
        {2, MIDDLE_TILE+BOARD_SIZE/4+1, 1},
        {2, MIDDLE_TILE-BOARD_SIZE/4-1, BOARD_SIZE},
        {2, MIDDLE_TILE+BOARD_SIZE/4+1, BOARD_SIZE},
        {2, 1, MIDDLE_TILE-BOARD_SIZE/4-1},
        {2, 1, MIDDLE_TILE+BOARD_SIZE/4+1},
        {2, BOARD_SIZE, MIDDLE_TILE-BOARD_SIZE/4-1},
        {2, BOARD_SIZE, MIDDLE_TILE+BOARD_SIZE/4+1},
        {2, MIDDLE_TILE-1, MIDDLE_TILE-1}, // around middle
        {2, MIDDLE_TILE-1, MIDDLE_TILE+1},
        {2, MIDDLE_TILE+1, MIDDLE_TILE-1},
        {2, MIDDLE_TILE+1, MIDDLE_TILE+1},
        {2, MIDDLE_TILE, 4},    // rest
        {2, MIDDLE_TILE-1, 3},
        {2, MIDDLE_TILE+1, 3},
        {2, MIDDLE_TILE, BOARD_SIZE-3},
        {2, MIDDLE_TILE-1, BOARD_SIZE-2},
        {2, MIDDLE_TILE+1, BOARD_SIZE-2},
        {2, 4, MIDDLE_TILE},
        {2, 3, MIDDLE_TILE-1},
        {2, 3, MIDDLE_TILE+1},
        {2, BOARD_SIZE-3, MIDDLE_TILE},
        {2, BOARD_SIZE-2, MIDDLE_TILE-1},
        {2, BOARD_SIZE-2, MIDDLE_TILE+1},
};

EXTERNC
void initializeBonuses(board_status_t *board) {
    for (int i = 0; i < AMOUNT_OF_BONUS; ++i) {
        // for proper board tile set the bonus
        board->board_tiles[bonus_tiles[i][BONUS_X]-1][bonus_tiles[i][BONUS_Y]-1].bonus = bonus_tiles[i][BONUS_T];
    }
}


// letter, points
const short all_letters[][2] {
        {'A', 1},
        {'B', 3},
        {'C', 3},
        {'D', 2},
        {'E', 1},
        {'F', 4},
        {'G', 2},
        {'H', 4},
        {'I', 1},
        {'J', 8},
        {'K', 5},
        {'L', 1},
        {'M', 3},
        {'N', 1},
        {'O', 1},
        {'P', 3},
        {'Q', 10},
        {'R', 1},
        {'S', 1},
        {'T', 1},
        {'U', 1},
        {'V', 4},
        {'W', 4},
        {'X', 8},
        {'Y', 4},
        {'Z', 10},
        {BLANK, 0},
};