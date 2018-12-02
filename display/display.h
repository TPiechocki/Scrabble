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

void bonusDescription(void);        // information about color bonuses

int boardXStart(void);          // return start coordinates for cursor
int boardYStart(void);

void displayBorder(void);       // display a border of a board
void displayBoard(board_status_t board);

void displayTiles(player_tile_t tiles[]);        //display player's tiles below a board
    // below every tile display number of points of this letter, 10 points = X
void displayTilesExchange(player_tile_t tiles[]);     // display tiles highlighting tiles to exchange

void displayWordCreate(player_t player);      // display a word to be inserted below a board
    // letters in player's hand have green background, letters not available with red background
void displayWordInsert(board_status_t *board, player_t *player);    // display word on a board
    // also handles situation, when word goes out of the board

// display board with border, legend and player's tiles
void displayAll(board_status_t board, player_t player);

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_DISPLAY_H
