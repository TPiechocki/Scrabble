//
// Created by Tomasz Piechocki on 02/12/2018.
//

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"../conio2.h"
#include"core.h"
#include"dictionary.h"


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
    dict_word_t *x = (dict_word_t *)malloc(sizeof(dict_word_t));
    if (x == NULL)
        return 1;
	x->word = (char *)malloc(sizeof(char)*(length+1));
	if (x->word == NULL) {
        free(x->word);
        free(x);
        return 1;
    }
    strcpy(x->word, word);
    x->next = NULL;
    previous->next = x;
    return 0;
}
// check if the word is in the dictionary somewhere, return 0 if yes, 1 if not
int checkWordInDictionary(char *word, dict_word_t head) {
    word = toLowerWord(word);
    dict_word_t *wordInDictionary = head.next;
    char txt[50];
    while (1) {
        if (strcmp(word, wordInDictionary->word) == 0) {
            return 0;
        }
        wordInDictionary = wordInDictionary->next;
        if (wordInDictionary->next == NULL)
            break;
    }
    sprintf(txt, "Word: \"%s\" is not in dictionary.", word);
    error(txt);
    return 1;
}
//  make the word including letters before and after word placed by player; buffer returned in array word
void beforeAfterWord(board_status_t board, player_t player, char word[BOARD_SIZE+1]) {
    int count = 0, length = strlen(player.word);
    if (player.word_orientation == HORIZONTAL) {
        // letters before the word
        for (int i = 1; board.board_tiles[board.xBoard-i-1][board.yBoard-1].tile != EMPTY; ++i) {
            count++;
        }
        // write them in proper order
        for (int i = count; i > 0; --i) {
            word[count - i] = (char)board.board_tiles[board.xBoard-i-1][board.yBoard-1].tile;
        }
        // concatenate the word itself
        strcat(word, player.word);
        count += length;
        // letters after word
        for (int i = length; board.board_tiles[board.xBoard+i-1][board.yBoard-1].tile != EMPTY; ++i) {
            word[count] = (char)board.board_tiles[board.xBoard+i-1][board.yBoard-1].tile;
            count++;
        }
        word[count+1] = '\0';
    }
    else if (player.word_orientation == VERTICAL) {
        // letters before the word
        for (int i = 1; board.board_tiles[board.xBoard-1][board.yBoard-i-1].tile != EMPTY; ++i) {
            count++;
        }
        // write them in proper order
        for (int i = count; i > 0; --i) {
            word[count - i] = (char)board.board_tiles[board.xBoard-1][board.yBoard-i-1].tile;
        }
        // concatenate the word itself
        strcat(word, player.word);
        count += length;
        // letters after word
        for (int i = length; board.board_tiles[board.xBoard-1][board.yBoard+i-1].tile != EMPTY; ++i) {
            word[count] = (char)board.board_tiles[board.xBoard-1][board.yBoard+i-1].tile;
            count++;
        }
        word[count+1] = '\0';
    }
}
//  look for word around the letter, position is the position of letter in a word which starts with 0
void aroundLetter(board_status_t board, player_t player, char word[BOARD_SIZE+1], int position) {
    // check for tiles which were on board before player's move
    if (player.word_orientation == HORIZONTAL) {
        if (board.board_tiles[board.xBoard+position - 1][board.yBoard - 1].tile == EMPTY) {
            int count = 0;
            // letters before player's letter
            for (int i = 1; board.board_tiles[board.xBoard+position - 1][board.yBoard - i - 1].tile != EMPTY; ++i) {
                count++;
            }
            // write them in proper order
            for (int i = count; i > 0; --i) {
                word[count - i] = (char) board.board_tiles[board.xBoard+position - 1][board.yBoard - i - 1].tile;
            }
            // add letter already from player's word
            word[count] = player.word[position];
            ++count;
            // letters after player's letter
            for (int i = 1; board.board_tiles[board.xBoard+position - 1][board.yBoard + i - 1].tile != EMPTY; ++i) {
                word[count] = (char) board.board_tiles[board.xBoard+position - 1][board.yBoard + i - 1].tile;
                count++;
            }
            word[count + 1] = '\0';
        }
    }
    else if (player.word_orientation == VERTICAL) {
        if (board.board_tiles[board.xBoard- 1][board.yBoard+position - 1].tile == EMPTY) {
            int count = 0;
            // letters before player's letter
            for (int i = 1; board.board_tiles[board.xBoard - i - 1][board.yBoard+position - 1].tile != EMPTY; ++i) {
                count++;
            }
            // write them in proper order
            for (int i = count; i > 0; --i) {
                word[count - i] = (char) board.board_tiles[board.xBoard - i - 1][board.yBoard+position - 1].tile;
            }
            // add letter already from player's word
            word[count] = player.word[position];
            ++count;
            // letters after player's letter
            for (int i = 1; board.board_tiles[board.xBoard + i - 1][board.yBoard+position - 1].tile != EMPTY; ++i) {
                word[count] = (char) board.board_tiles[board.xBoard + i - 1][board.yBoard+position - 1].tile;
                count++;
            }
            word[count + 1] = '\0';
        }
    }
}

EXTERNC
int createDictionary(const char *fileName, board_status_t *board) {
    clrscr();
    gotoxy(15, 15);
    cputs("Loading dictionary...");
    // fill with words
    FILE *words = fopen(fileName, "r");
    if (words == NULL) {
        return 2;
    }
    // initialisation
    board->dictionaryHead.next = NULL;
    char word[100];
    dict_word_t *previous = &board->dictionaryHead;
    while (1) {
        int status = fscanf(words, "%s\n", word);       // returns 1 if ok
		int length = strlen(word);

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
    clrscr();
    return 0;
}

EXTERNC
int checkDictionary(board_status_t board, player_t player) {
    char word[BOARD_SIZE+1] = "\0";
    // search whether there are letters before or after inserted word
    beforeAfterWord(board, player, word);
    if (checkWordInDictionary(word, board.dictionaryHead) == 1) {
        return 1;
    }
    memset(word, '\0', BOARD_SIZE+1);   // clear the whole word
    // search for new words around new letters
    for (int i = 0; player.word[i] != '\0' ; ++i) {
        aroundLetter(board, player, word, i);
        if (strlen(word) > 1 && checkWordInDictionary(word, board.dictionaryHead) == 1) {
            return 1;
        }
    }
    return 0;   // when all letters are in dictionary
}

EXTERNC
void clearDictionary(dict_word_t *head) {
    while (head->next != NULL) {
        dict_word_t *temp = head->next;
        head->next = head->next->next;
        free(temp->word);
        free(temp);
    }
}
