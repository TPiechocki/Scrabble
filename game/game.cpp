//
// Created by Tomasz Piechocki on 21/11/2018.
//

#include"game.h"

#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC    extern "C"
#else
#define EXTERNC
#endif


int checkLetter(board_status_t *board, player_t *player) {      // check if letter can be placed
    int check_player = 1, check_board  = 1;                     // return 0 if possible, 1 if not
    for (int i = 0; i < PlAYER_TILES; ++i) {                    // check if player has letter
        if (player->tiles[i] == player->letter) {
            check_player = 0;
            break;
        }
    }
    if (board->board_tiles[boardXPosition(board->x)-1][boardYPosition(board->y)-1].tile == EMPTY)
        check_board = 0;                                // check if tile on board is available
    if (check_player == 0 && check_board == 0)          // both conditions must be ok
        return 0;
    else
        return 1;
}

EXTERNC
void emptyBoard(board_status_t *board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board->board_tiles[i][j].tile = EMPTY;
            board->board_tiles[i][j].bonus = EMPTY;
        }
    }
}

EXTERNC
void insertLetter(board_status_t *board, player_t *player) {
    if (checkLetter(board, player) == 0) {              // check if move is possible
        board->board_tiles[boardXPosition(board->x)-1][boardYPosition(board->y)-1].tile = player->letter;
        (boardYPosition(board->y) > 1)?board->y--:board->y++;       // move cursor one up or down
        for (int i = 0; i < PlAYER_TILES; ++i) {
            if (player->tiles[i] == player->letter) {
                player->tiles[i] = EMPTY;
                break;
            }
        }
    }
    else
        error("Bad letter");
}
