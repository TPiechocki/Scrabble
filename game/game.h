//
// Created by Tomasz Piechocki on 21/11/2018.
//
// definitions of consts, structures for game status and functions connected with game
//

#ifndef SCRABBLE_GAME_H
#define SCRABBLE_GAME_H

#include"../core/core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char tiles[PlAYER_TILES];
    char letter;
    // int points;
} player_t;

typedef struct {
    int tile;       // EMPTY or letter
    int bonus;      // EMPTY, negative for word bonus or positive for letter bonus
} board_tile_t;


typedef struct {
    int ch;         // key code
    int text_color;
    int background_color;
    int zero;       // check whether key has two character code
    int x;          // position of cursor
    int y;
    board_tile_t board_tiles[BOARD_SIZE][BOARD_SIZE];
} board_status_t;

void emptyBoard(board_status_t *board);     // fill board tiles with EMPTY

void insertLetter(board_status_t *board, player_t *player);     // insert a letter on board if player can

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_GAME_H
