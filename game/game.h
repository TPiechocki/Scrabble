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

// info about each of player's tiles
typedef struct {
    char letter;
    short used;     // 0 if not used in actual word, 1 if used
                    // also 1 if player want to exchange this letter
} player_tile_t;
// store a status of player's actions and general info about each player
typedef struct {
    player_tile_t tiles[PLAYER_TILES];  // tiles in player's hand
    char word[BOARD_SIZE+1];            // word which player tries to insert
    short word_status[BOARD_SIZE];      // 0 if player doesn't have letter, 1 if has, -1 if it's blank
                                        // also stores bonus multiplier for letter
    short word_orientaion = VERTICAL;   // vertical or horizontal
} player_t;

void emptyBoard(board_status_t *board);     // fill board tiles with EMPTY

void insertWord(board_status_t *board, player_t *player);   // insert a word on board

void takeLetters(board_status_t *board, player_t *player);    // take letters from pool

void exchangeTiles(board_status_t *board, player_t *player);    // player exchange chosen tiles

int endOfGame(player_t player, board_status_t board);     // check if player has no tiles, if yes display end message

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_GAME_H
