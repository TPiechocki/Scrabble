//
// Created by Tomasz Piechocki on 20/11/2018.
//

#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include"../conio2.h"
#include"display.h"

#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC    extern "C"
#else
#define EXTERNC
#endif

EXTERNC
void displayLegend(board_status_t board) {
    int count = 1;
    char txt[32];
    gotoxy(LEGEND_POSITION, count++);
    cputs("Tomasz Piechocki, 175690");
    gotoxy(LEGEND_POSITION, count++);
    cputs("Implemented: a, b, c, d, e");
    count++;

    gotoxy(LEGEND_POSITION, count++);
    cputs("arrows  = move cursor");
    gotoxy(LEGEND_POSITION, count++);
    cputs("i       = insert letter");
    gotoxy(LEGEND_POSITION, count++);
    cputs("n       = new game");
    gotoxy(LEGEND_POSITION, count++);
    cputs("space   = change color");
    gotoxy(LEGEND_POSITION, count++);
    cputs("enter   = change background color");
    gotoxy(LEGEND_POSITION, count++);
    cputs("q       = exit");
    count++;

    sprintf(txt, "actual position: (%2d,%2d)", boardXPosition(board.x), boardYPosition(board.y));
    gotoxy(LEGEND_POSITION, count++);
    cputs(txt);
    if (board.zero) sprintf(txt, "key code: 0x00 0x%02x", board.ch);    //code of last pressed key
    else sprintf(txt, "key code: 0x%02x", board.ch);
    gotoxy(LEGEND_POSITION, count++);
    cputs(txt);

}

EXTERNC
int boardXStart(void) {
    return BOARD_POSITION + BOARD_PADDING + 1;
}

EXTERNC
int boardYStart(void) {
    return BOARD_PADDING + 1;
}

EXTERNC
void displayBorder(){
    for (int i = 0; i <= BOARD_SIZE + 1; i++) {
        for (int j = 0; j <= BOARD_SIZE + 1; j++)
            if (i==0 || i == BOARD_SIZE + 1 || j == 0 || j == BOARD_SIZE +1) {
                gotoxy(i+BOARD_PADDING+BOARD_POSITION, j+BOARD_PADDING);
                textbackground(WHITE);
                putch(' ');
            }
    }
}

EXTERNC
void displayBoard(board_status_t *board) {
    textattr(BLACK*16 + WHITE);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            gotoxy(i+BOARD_PADDING+BOARD_POSITION+1, j+BOARD_PADDING+1);
            switch (board->board_tiles[i][j].tile) {
                case EMPTY:
                    putch(' ');
                    break;
                default:
                    putch(board->board_tiles[i][j].tile);
            }
        }
    }
}

EXTERNC
void displayTiles(char tiles[], int size) {
    for (int i = 0; i < size; ++i) {
        gotoxy(BOARD_POSITION + BOARD_PADDING + 2*i + 2, 2*BOARD_PADDING + BOARD_SIZE + 1);
        textattr(WHITE*16+BLACK);
        putch(tiles[i]);
    }
}
