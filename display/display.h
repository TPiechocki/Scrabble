//
// Created by Tomasz Piechocki on 20/11/2018.
//
// functions which display everything in console
//

#ifndef SCRABBLE_DISPLAY_H
#define SCRABBLE_DISPLAY_H

#include"../game/game.h"       //structures: board_status_t and defined consts

#ifdef __cplusplus
extern "C" {
#endif

void displayLegend(board_status_t board);   //display a legend, ch is a code of last pressed key
                                        // and zero says whether it is special key like e.g. arrows
                                        // with two characters, x and y is the actual position of cursor



int boardXStart(void);          // return start coordinates for cursor
int boardYStart(void);

void displayBorder();       // display a border of a board
void displayBoard(board_status_t *board);

void displayTiles(char tiles[], int size);        //display player's tiles below a board

void displayWord();

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_DISPLAY_H
