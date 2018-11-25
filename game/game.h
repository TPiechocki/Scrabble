//
// Created by Tomasz Piechocki on 21/11/2018.
//
// definitions of consts, structures for game status and functions connected with game
//

#ifndef SCRABBLE_GAME_H
#define SCRABBLE_GAME_H

#include"../core/core.h"

#define HORIZONTAL 0
#define VERTICAL 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char letter;
    short used;     // 0 if not used in actual word, 1 if used
} player_tile_t;

typedef struct {
    player_tile_t tiles[PLAYER_TILES];  // tiles in player's hand
    char word[BOARD_SIZE+1];            // word which player tries to insert
    short word_status[BOARD_SIZE];      // 0 if player doesn't have letter, 1 if has
    short word_orientaion = VERTICAL;              // vertical or horizontal
    // int points;
} player_t;

void emptyBoard(board_status_t *board);     // fill board tiles with EMPTY

void insertWord(board_status_t *board, player_t *player);   // insert a word on board

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_GAME_H
