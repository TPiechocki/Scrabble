//
// Created by Tomasz Piechocki on 21/11/2018.
//

#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include"../conio2.h"
#include"game.h"
#include"../display/display.h"

#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC    extern "C"
#else
#define EXTERNC
#endif

// restart a status of word being inserted
void restartWordStatus(player_t *player) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        player->word_status[i] = 0;
    }
    for (int j = 0; j < PLAYER_TILES; ++j) {
        player->tiles[j].used = 0;
    }
}
// check if letter is in player's hand, if yes it change status of word and change tile to used, includes BLANKs
int checkLetterUsed(player_t *player, int i) {     // returns 1 if it change something
    for (int j = 0; j < PLAYER_TILES; ++j) {
        // check for letter
        if (player->word[i] == player->tiles[j].letter && player->tiles[j].used == 0) {
            player->word_status[i] = 1;
            player->tiles[j].used = 1;
            return 1;
        }
    }
    for (int j = 0; j < PLAYER_TILES; ++j) {
        // check for blank if it's not letter
        if (-1 == player->tiles[j].letter && player->tiles[j].used == 0) {
            player->word_status[i] = 1;
            player->tiles[j].used = 1;
            return 1;
        }
    }
    return 0;
}
// funtion which checks whether player has a letter in his tiles and if it wasn't used yet in this word
void checkLetter(player_t *player) {
	restartWordStatus(player);
    for (int i = 0; player->word[i] != '\0'; ++i) {
        checkLetterUsed(player, i);
    }
}
// check if the first move is through the middle
int checkFirstMove (board_status_t *board, player_t *player) {
    boardPosition(board);
    if (player->word_orientaion == HORIZONTAL) {
        if (board->yBoard == MIDDLE_TILE) {
            for (int i = 0; player->word[i] != '\0'; ++i) {
                if (board->xBoard + i == MIDDLE_TILE) {
                    board->firstMove = 0;
                    return 0;
                }

            }
        }
    }
    else if (player->word_orientaion == VERTICAL) {
        if (board->xBoard == MIDDLE_TILE) {
            for (int i = 0; player->word[i] != '\0'; ++i) {
                if (board->yBoard + i == MIDDLE_TILE) {
                    {
                        board->firstMove = 0;
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
// check for other words than first if at least one board tile, under word to placed, contains a letter
int checkMove(board_status_t *board, player_t *player) {
    boardPosition(board);
    if (player->word_orientaion == HORIZONTAL) {
        for (int i = 0; player->word[i] != '\0' ; ++i) {
            if (board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile != EMPTY)
                return 0;
        }
    }
    else if (player->word_orientaion == VERTICAL) {
        for (int i = 0; player->word[i] != '\0' ; ++i) {
            if (board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile != EMPTY)
                return 0;
        }
    }
    return 1;
}
//check if word can be placed in given position, first time checks including blank
int checkWord (board_status_t *board, player_t *player) {
    int length = strlen(player->word);
    boardPosition(board);
    restartWordStatus(player);
    if (board->firstMove) {     // first move
        if (checkFirstMove(board, player)) {   // if first move is not through the middle tile
            return 2;
        }
    }
    else {      // not a frist move
        if (checkMove(board, player)) {       // if none of the letters is already on board
            return 3;
        }
    }
    if (player->word_orientaion == HORIZONTAL) {
        for (int i = 0; i < length; ++i) {
            if (board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile != EMPTY &&
               board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile != player->word[i]) {
                    return 1;
            }
            else if (board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile == EMPTY) {
                int status = 1;
                if (checkLetterUsed(player, i))     // if it is ok change status
                    status = 0;
                if (status == 1)
                    return 1;
            }
        }
    }
    else if (player->word_orientaion == VERTICAL) {
        for (int i = 0; i < length; ++i) {
            if(board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile != EMPTY &&
               board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile != player->word[i]) {
                return 1;
            }
            else if (board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile == EMPTY) {
                int status = 1;
                if (checkLetterUsed(player, i))     // if it is ok change status
                    status = 0;
                if (status == 1)
                    return 1;
            }
        }
    }
	return 0;
}
// function to create a word below a board before putting it on board
// returns enter(confirmed word), escape(cancelled word) or 1(error)
int createWord(board_status_t *board, player_t *player) {
    gotoxy(5,23);
    cputs("Insert a word. Green letters are availabe in your tiles and reds are not.");
    gotoxy(5,24);
    cputs("Letter turns green if there is tile not used earlier in this word. Blanks are skipped here.");
    char letter = 0;            // change everything to needed defaults
    int wordcount = 0;
    strcpy(player->word, "\0"); // empty word at start
    restartWordStatus(player);
    while (board->ch != 0x0d && board->ch != 0x1b) {    // loop which ends with esc or enter
        board->ch = getch();
        if (board->ch == '\b') {            // backspace to delete last letter
            if (wordcount > 0) {
                wordcount--;
                player->word[wordcount] = '\0';
            }
        }
        else if (wordcount < BOARD_SIZE) {  // check if word is not too long
            letter = toUpper((char)board->ch);  // convert to upper and check if it's letter, esc or enter
            if (letter >= 'A' && letter <= 'Z') {
                player->word[wordcount] = letter;
                player->word[wordcount + 1] = '\0';
                wordcount++;
            }
            else if (letter != 0x0d && letter != 0x1b){
                error("Bad letter. Insert the word again.");
                strcpy(player->word, "\0");
                break;
            }       // for enter and escape nothing
        }
        checkLetter(player);    // check which letters are in player's tiles
        displayWordCreate(*player);
    }
    if (letter == 0x0d || letter == 0x1b)       // to check if confrm or cancel
        return letter;
    else return 1;                              // error, end without enter or esc
}
// display position on board and change it with cursor movement
int positionWord(board_status_t *board, player_t *player) {
    player->word_orientaion = HORIZONTAL;
    displayWordInsert(board, player);
    int ch = 0;
    while (ch != '0x0d' && ch !='0x1b') {       // wait for enter or escape
        ch = getch();
        switch (ch) {
            case 0:     // arrow which moves cursor
                ch = readArrow(getch());
                moveCursor(board, ch);
                break;
            case 'o':   // change word orientation
                if (player->word_orientaion == HORIZONTAL)
                    player->word_orientaion = VERTICAL;
                else
                    player->word_orientaion = HORIZONTAL;
                break;
            case 0x0d:      // enter to confirm
            case 0x1b:      // esc to cancel action
                return ch;
            default:
                error("Unknown opertaion. Try again.");
                displayBorder();
                displayTiles(player->tiles, PLAYER_TILES);
                break;
        }
        displayBoard(board);
        displayWordInsert(board, player);
        displayLegend(*board);
    }
    return 1;
}
// place a word on the board if it can be done
void placeWord(board_status_t *board, player_t *player) {
    boardPosition(board);
    int length;
    int check = 1;      // check if at least one tile was used
    int status = checkWord(board,player);
    switch (status) {
        case 0:
            length = strlen(player->word);
            if (player->word_orientaion == HORIZONTAL) {
                for (int i = 0; i < length; ++i) {
                    board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile = player->word[i];
                }
            } else {
                for (int i = 0; i < length; ++i) {
                    board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile = player->word[i];
                }
            }
            for (int i = 0; i < PLAYER_TILES; ++i) {        // remove used tiles from hand
                if (player->tiles[i].used == 1) {
                    player->tiles[i].used = 0;
                    player->tiles[i].letter = EMPTY;
                    check = 0;
                }
            }
            if (check)
                error("All tiles were already on the board.");
            break;
        case 1:
            error("You can't put this word here.");
            break;
        case 2:
            error("Frist word must go thourgh the middle.");
            break;
        case 3:
            error("Placed word must contain at least one letter alreay on board.");
            break;
        default:
            error("Unknown error.");
            break;
    }
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
void insertWord(board_status_t *board, player_t *player) {
    int status = createWord(board, player);
    if (player->word[0] == '\0')
        return;
    if (status == 0x0d) {
        status = positionWord(board, player);
        if (status == 0x0d) {
            placeWord(board, player);        // place a word and check if it can be there
        }
    }
}
