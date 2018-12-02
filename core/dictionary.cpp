//
// Created by Tomasz Piechocki on 02/12/2018.
//

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"dictionary.h"
#include"core.h"
#include "dictionary.h"


#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

// returns 1 if malloc returned null, if everything is okay returns 0
// add the word to the list with given previous element, word to insert and length of this word
int addWord(dict_word_t *previous, char *word, int length) {
    dict_word_t *x = (dict_word_t *)malloc(sizeof(dict_word_t*));
    if (x == NULL)
        return 1;
	x->word = (char *)malloc(sizeof(char)*(length + 1));
	if (x->word == NULL)
		return 1;
    strcpy(x->word, word);
    x->next = NULL;
    previous->next = x;
    return 0;
}

EXTERNC
int createDictionary(const char *fileName, dict_word_t *head_main) {
    // initialisation
    dict_word_t head;
    head.next = NULL;
    // fill with words
    FILE *words = fopen(fileName, "r");
    if (words == NULL) {
        error("This dictionary does not exist.");
        return 1;
    }
    int length;
    char word[100];
	int status = 0;
    dict_word_t *previous = &head;
    while (1) {
        status = fscanf(words, "%s\n", word);       // returns 1 if ok
		length = strlen(word);

		// add word  when there is enough free memory
        if (addWord(previous, word, length) != 0) {
            error("Not enough space for that dictionary.");
            return 1;
        }
        previous = previous->next;
        if (status == EOF) {    // end when end of file
            break;
        }
        if (status != 1) {      // if something different than EOF or 1
            error("Undefined error.");
            return 1;
        }
    }
    fclose(words);
	
    FILE *test = fopen("test.txt", "w");
    dict_word_t *xxx = head.next;
    while (1) {
       fprintf(test, "%s\n", xxx->word);
       xxx = xxx->next;
       if (xxx->next == NULL)      // to not skip last item
           break;
    }
    fclose(test);
    head_main = head.next;      // change head_main which was argument of function
    return 0;
}

EXTERNC
void deleteDictionary(dict_word_t *head) {
    if (head->next == NULL) // nothing to free
        return;
    dict_word_t *next = head->next;
    dict_word_t *temp;
    while (1) {
        if (next->next == NULL) {     // when last
            free(next);
            break;
        }
        // else
        temp = next;
        next = next->next;
        free(temp);

    }
}
