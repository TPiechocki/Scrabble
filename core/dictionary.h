//
// Created by Tomasz Piechocki on 02/12/2018.
//
// handle everything connected to dictionary
// every after word in dictionary there is new line symbol in Windows style (CRLF)
// other files can cause obviously errors
//

#ifndef SCRABBLE_DICTIONARY_H
#define SCRABBLE_DICTIONARY_H

#include"../game/game.h"

#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC    extern "C"
#else
#define EXTERNC
#endif

#ifdef __cplusplus
extern "C" {
#endif

// create a dictionary in one direction list, returns 1 if something went wrong
// dictionary is created from a file where every word is in a new line
// fileName - name of dictionary file; head - place from caller where head of list will be stored
int createDictionary(const char *fileName, board_status_t *board);

// clear memory allocated for dictionary
void clearDictionary(dict_word_t *head);

// check if word is in dictionary
int checkDictionary(board_status_t board, player_t player);

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_DICTIONARY_H
