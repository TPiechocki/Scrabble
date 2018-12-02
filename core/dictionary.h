//
// Created by Tomasz Piechocki on 02/12/2018.
//
// handle everything connected to dictionary
//

#ifndef SCRABBLE_DICTIONARY_H
#define SCRABBLE_DICTIONARY_H

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

typedef struct dict_word {
    char *word;
    struct dict_word *next;
}dict_word_t;

// create a dictionary in one direction list, returns 1 if something went wrong
// dictionary is created from a file where every word is in a new line
// fileName - name of dictionary file; head - place from caller where head of list will be stored
int createDictionary(const char *fileName, dict_word_t *head);

// free all the space of dictionary, argument is the head of the list
void deleteDictionary(dict_word_t *head);

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_DICTIONARY_H
