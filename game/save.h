//
// Created by Tomasz Piechocki on 01/12/2018.
//
// Save and load state of a game
//


#ifndef SCRABBLE_SAVE_H
#define SCRABBLE_SAVE_H

#include"game.h"

#ifdef __cplusplus
extern "C" {
#endif

void saveGame(board_status_t *board, player_t *player, char *dictionary);
void loadGame(board_status_t *board, player_t *player, char *dictionary);

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_SAVE_H

