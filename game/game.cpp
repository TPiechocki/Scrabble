//
// Created by Tomasz Piechocki on 21/11/2018.
//

#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include <stdlib.h>
#include"../conio2.h"
#include"game.h"
#include"../display/display.h"
#include"../core/dictionary.h"


#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC    extern "C"
#else
#define EXTERNC
#endif

void restartWordStatus(player_t *player) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        player->word_status[i] = 0;
    }
    for (int j = 0; j < PLAYER_TILES; ++j) {
        player->tiles[j].used = 0;
    }
}

// check if letter is in player's hand, if yes it change status of word and change tile to used, includes BLANKs
int checkLetterUsed(player_t *player, int i) {     // returns 1 if it change something, 2 if it was blank
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
        if (BLANK == player->tiles[j].letter && player->tiles[j].used == 0) {
            player->word_status[i] = -1;
            player->tiles[j].used = 1;
            return 2;
        }
    }
    return 0;
}
// function which checks whether player has a letter in his tiles and if it wasn't used yet in this word
void checkLetter(player_t *player) {
	restartWordStatus(player);
    for (int i = 0; player->word[i] != '\0'; ++i) {
        checkLetterUsed(player, i);
    }
}
// check if player has all needed tiles in hand
int checkFirstMoveLetters(player_t *player) {
    for (int i = 0; player->word[i] != '\0' ; ++i) {
        if (player->word_status[i] == 0) {
            return 1;
        }
    }
    return 0;
}
// check if the first move is through the middle
int checkFirstMove (board_status_t *board, player_t *player) {
    boardPosition(board);
    if (player->word_orientation == HORIZONTAL) {
        if (board->yBoard == MIDDLE_TILE) {
            for (int i = 0; player->word[i] != '\0'; ++i) {
                if (board->xBoard + i == MIDDLE_TILE) {
                    return 0;
                }

            }
        }
    }
    else if (player->word_orientation == VERTICAL) {
        if (board->xBoard == MIDDLE_TILE) {
            for (int i = 0; player->word[i] != '\0'; ++i) {
                if (board->yBoard + i == MIDDLE_TILE) {
                    {
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
    if (player->word_orientation == HORIZONTAL) {
        for (int i = 0; player->word[i] != '\0' ; ++i) {
            if (board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile != EMPTY)
                return 0;
        }
    }
    else if (player->word_orientation == VERTICAL) {
        for (int i = 0; player->word[i] != '\0' ; ++i) {
            if (board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile != EMPTY)
                return 0;
        }
    }
    return 1;
}
//check if word can be placed in given position
int checkWord (board_status_t *board, player_t *player) {   // returns 0 for norm
    int length = strlen(player->word);
    boardPosition(board);
    restartWordStatus(player);
    if (board->firstMove) {     // first move
        if (checkFirstMove(board, player)) {   // if first move is not through the middle tile
            return 2;
        }
    }
    else {      // not a first move
        if (checkMove(board, player)) {       // if none of the letters is already on board
            return 3;
        }
    }
    if (player->word_orientation == HORIZONTAL) {
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
    else if (player->word_orientation == VERTICAL) {
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
    gotoxy(5,38);
    cputs("Insert a word. Green letters are availabe in your tiles and reds are not.");
    gotoxy(5,39);
    cputs("Blanks take first possible place.");
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
    if (letter == 0x0d || letter == 0x1b)       // to check if confirm or cancel
        return letter;
    else return 1;                              // error, end without enter or esc
}
// display position on board and change it with cursor movement
int positionWord(board_status_t *board, player_t *player) {
    player->word_orientation = HORIZONTAL;
    displayWordInsert(board, player);
    int ch = 0;
    while (ch != 0x0d && ch !=0x1b) {       // wait for enter or escape
        ch = getch();
        switch (ch) {
            case 0:     // arrow which moves cursor
                ch = readArrow(getch());
                moveCursor(board, ch);
                break;
            case 'o':   // change word orientation
                if (player->word_orientation == HORIZONTAL)
                    player->word_orientation = VERTICAL;
                else
                    player->word_orientation = HORIZONTAL;
                break;
            case 0x0d:      // enter to confirm
            case 0x1b:      // esc to cancel action
                return ch;
            default:
                error("Unknown opertaion. Try again.");
                displayAll(*board, *player);
                break;
        }
        displayBoard(*board);
        displayWordInsert(board, player);
        displayLegend(*board);
    }
    return 1;
}

// check if player used all tiles, if yes return 50, else 0
int allTilesUsedPoints(player_t *player) {
    for (int i = 0; i < PLAYER_TILES; ++i) {
        if (player->tiles[i].used == 0)
            return 0;
    }
    return 50;
}

// count points for the word
// arguments: board struct, word, length of word, word orientation and coordinates relative to board(from 1)
int wordPoints(board_status_t board, char *word, int length, int orientation, int x, int y) {
    int points = 0, multiplier = 1, letterbonus;     // word multiplier
    if (orientation == HORIZONTAL) {
        for (int i = 0; i < length; ++i) {
            letterbonus = 1;
            if (board.board_tiles[x+i-1][y-1].bonus < 0)
                multiplier *= abs(board.board_tiles[x+i-1][y-1].bonus);
            else if (board.board_tiles[x+i-1][y-1].bonus > 0)
                letterbonus *= abs(board.board_tiles[x+i-1][y-1].bonus);
            points += all_letters[word[i]-'A'][LETTER_POINTS] * letterbonus;
        }
    }
    else if (orientation == VERTICAL) {
        for (int i = 0; i < length; ++i) {
            letterbonus = 1;
            if (board.board_tiles[x-1][y+i-1].bonus < 0)
                multiplier *= abs(board.board_tiles[x-1][y+i-1].bonus);
            else if (board.board_tiles[x-1][y+i-1].bonus > 0)
                letterbonus *= abs(board.board_tiles[x-1][y+i-1].bonus);
            points += all_letters[word[i]-'A'][LETTER_POINTS] * letterbonus;
        }
    }
    return points * multiplier;
}

// count points of all words which was created with this move
// specific comments just for first word creation, because all 4 parts are quite similar
int countPoints(board_status_t *board, player_t *player) {
    int points = 0, x = board->xBoard, y = board->yBoard, count = 0;
    char word[BOARD_SIZE+1] = "\0";
    // main word extended with letters just before or after placed word
    if (player->word_orientation == HORIZONTAL) {
        // look for letters before first player's word letter and move start coordinates
        while (board->board_tiles[x-2][y-1].tile != EMPTY) {
            --x;
        }
        for (int i = 0; i < board->xBoard - x; ++i) {
            word[count++] = (char)board->board_tiles[x-1+i][y-1].tile;
        }
        // add the part which is a player's word
        strcat(word, player->word);
        count += strlen(player->word);
        // look for letters just after player's word
        for (int i = 0; board->board_tiles[board->xBoard+strlen(player->word)-1+i][y-1].tile != EMPTY; ++i) {
            word[count++] = (char)board->board_tiles[board->xBoard+strlen(player->word)-1+i][y-1].tile;
        }
    }
    else if (player->word_orientation == VERTICAL) {
        while (board->board_tiles[x-1][y-2].tile != EMPTY) {
            --y;
        }
        for (int i = 0; i < board->yBoard - y; ++i) {
            word[count++] = (char)board->board_tiles[x-1][y-1+i].tile;
        }
        strcat(word, player->word);
        count += strlen(player->word);
        for (int i = 0; board->board_tiles[x-1][board->yBoard+strlen(player->word)-1+i].tile != EMPTY; ++i) {
            word[count++] = (char)board->board_tiles[x-1][board->yBoard+strlen(player->word)-1+i].tile;
        }
    }
    points += wordPoints(*board, word, strlen(word), player->word_orientation, x, y);
	memset(word, '\0', BOARD_SIZE + 1);   // clear the whole word
    // new words around placed letters, quite similar to looking for words to check with dictionary
    if (player->word_orientation == HORIZONTAL) {           // then possible vertical new other words
        for (unsigned int i = 0; i < strlen(player->word); ++i) {
            if (board->board_tiles[board->xBoard-1+i][board->yBoard-1].tile == EMPTY) {
                x = board->xBoard + i, y = board->yBoard, count = 0;
                memset(word, '\0', BOARD_SIZE + 1);   // clear the whole word
                while (board->board_tiles[x - 1][y - 2].tile != EMPTY) {
                    --y;
                    ++count;
                }
                for (int j = 0; j < count; ++j) {
                    word[j] = (char) board->board_tiles[x - 1][y - 1 + j].tile;
                }
                word[count++] = player->word[i];    // this time player's part is just a one letter
                for (int j = 0; board->board_tiles[x - 1][y - 1 + count].tile != EMPTY; ++j) {
                    word[count] = (char) board->board_tiles[x - 1][y - 1 + count].tile;
                    ++count;
                }
            }
			if (strlen(word) > 1) {
				points += wordPoints(*board, word, strlen(word), (player->word_orientation + 1) % 2, x, y);
			}
        }
    }
    else if (player->word_orientation == VERTICAL) { // then possible horizontal new other words
        for (unsigned int i = 0; i < strlen(player->word); ++i) {
            if (board->board_tiles[board->xBoard-1][board->yBoard-1+i].tile == EMPTY) {
                x = board->xBoard, y = board->yBoard + i, count = 0;
                memset(word, '\0', BOARD_SIZE + 1);   // clear the whole word
                while (board->board_tiles[x - 2][y - 1].tile != EMPTY) {
                    --x;
                    ++count;
                }
				for (int j = 0; j < count; ++j) {
                    word[j] = (char) board->board_tiles[x - 1 + j][y - 1].tile;
                }
                word[count++] = player->word[i];
                for (int j = 0; board->board_tiles[x - 1 + count][y - 1].tile != EMPTY; ++j) {
                    word[count] = (char) board->board_tiles[x - 1 + count][y - 1].tile;
                    ++count;
                }
            }
			if (strlen(word) > 1) {
				points += wordPoints(*board, word, strlen(word), (player->word_orientation + 1) % 2, x, y);
			}
        }
    }
    return points;
}
// place a word on the board if it can be done also counts points
void placeWord(board_status_t *board, player_t *player) {
    boardPosition(board);
    int points = 0, check = 1, length = strlen(player->word);
    // multiplier is a word bonus, check for testing if all tiles were already on board, if yes then 1
    // length is the length of the word
    int status = checkWord(board,player); // check if word can be placed in this position
    switch (status) {
        case 0:
            if (checkDictionary(*board, *player) == 1) {        // check all new words with dictionary
                return;
            }
            if (board->firstMove == 1)  // if first move and all checks passed
                board->firstMove = 0;   // then first move is made
            // count points
            for (int i = 0; i < PLAYER_TILES; ++i) {        // remove used tiles from hand
                if (player->tiles[i].used == 1) {
                    player->tiles[i].used = 0;
                    player->tiles[i].letter = EMPTY;
                    check = 0;      // if at least one letter was used than it means the player added letter
                }
            }
            if (check) {      // if all tiles were already on board before this move
                error("All tiles were already on the board.");
                break;
            }
            // count points of all new words
            points += countPoints(board, player);
            // put the word on board, if all checks were positive
            if (player->word_orientation == HORIZONTAL) {
                for (int i = 0; i < length; ++i) {
                    board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile = player->word[i];
                    // remove bonus value
                    board->board_tiles[board->xBoard+i-1][board->yBoard-1].bonus = 0;   // set bonus to 0
                }
            }
            else {
                for (int i = 0; i < length; ++i) {
                    board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile = player->word[i];
                    // remove bonus value
                    board->board_tiles[board->xBoard-1][board->yBoard+i-1].bonus = 0;   // set bonus to 0
                }
            }

            points += allTilesUsedPoints(player);

            board->points[board->player] += points;     // add calculated points to player's score

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

// functions used in exchange of tiles
// choose tiles and highlight them with background color
void chooseTiles(board_status_t *board, player_t *player) {
    restartWordStatus(player);
    int choice = 0;
    do {        // loop ends with confirmation of enter or 'w'
        int count = 0; // count number of letters chosen
        for (int i = 0; i < PLAYER_TILES; ++i) {    // count amount of letters which player want to exchange
            if (player->tiles[i].used == 1)
                ++count;
        }
        if (count > board->remaining_letters) {     // if player want to exchange more letters than left in pool
            error("You can't exchange more letters than letters left in a pool.");
            restartWordStatus(player);
            displayAll(*board, *player);
        }
        displayTilesExchange(player->tiles);        // display with highlighted ones
        choice = getch();
        if (choice > '0' && choice <= '0' + PLAYER_TILES && player->tiles[choice-'1'].letter != EMPTY) {
            ++player->tiles[choice-'0' - 1].used %= 2;  // switch between 0 and 1
        }
        else if (choice == 0x0d || choice == 'w') {
            /* void, these characters ends a loop */
        }
        else {
            error("You have to provide number from 1 to 7 to choose tile or enter/w to confirm move.");
            displayAll(*board, *player);
        }
    } while (choice != 0x0d && choice != 'w');
}

// check if the word created by player can be placed anywhere on the board
int checkCreatedWord(board_tile_t board[BOARD_SIZE][BOARD_SIZE], player_t player) {
    int length = strlen(player.word), lacking = 0;
    for (int i = 0; i < length; ++i) {
        if (player.word_status[i] == 0)     // if not in player's tiles
            lacking++;      // amount of letter lacking in player's hands
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {		// j is x coord of board array and i is y coord
        for (int j = 0; j < BOARD_SIZE; ++j) {	// for every tile on board
            for (int k = 0; k < length; ++k) {  // for every letter in word
				if (player.word[k] == board[j][i].tile) {  // if letter from word is in this tile

					// count stands for lacking letters and it is decremented if needed tile is in good posistion
					// it can be negative if blank is not used in a move

					// check horizontally
					if (j + (length - k) <= BOARD_SIZE && j - k >= 0) {		// if word is not too long
						for (int l = 0, status = 0, count = lacking; l < length; ++l) {
							// if tile on board is different than word letter, than word is not allowed in this place
							if (board[j - k + l][i].tile != EMPTY && board[j - k + l][i].tile != player.word[l])
								status = 1;
							// reduce by one if letter not available in hand or used with blank is the same as the letter on board
							if (player.word_status[l] <= 0 && board[j - k + l][i].tile == player.word[l])
								--count;
							if (l == (length-1) && status == 0 && count <= 0)	// if nothing is wrong for the whole word
								return 0;
						}
					}
					// check vertically
					if (i + (length - k) <= BOARD_SIZE && i - k >= 0) {		// if word is not too long
						for (int l = 0, status = 0, count = lacking; l < length; ++l) {
							// if tile on board is different than word letter, than word is not allowed in this place
							if (board[j][i - k + l].tile != EMPTY && player.word[l] != board[j][i - k + l].tile)
								status = 1;
							// reduce by one if letter not available in hand or used with blank is the same as the letter on board
							if (player.word_status[l] <= 0 && board[j][i - k + l].tile == player.word[l])
								--count;
							if (l == (length-1) && status == 0 && count <= 0)	// if nothing is wrong for the whole word
								return 0;
						}
					}
				}
            }
        }

    }
    return 1;	// if there was no proper place then return 0
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
    int status = createWord(board, player);     // create word below a board, enter to confirm
    if (status == 0x0d) {
        if (player->word[0] == '\0') {  // check if word created is not empty
            error("Word can't be empty.");
            return;
        }
        // check if player has all letters
        if(board->firstMove == 1 && checkFirstMoveLetters(player) == 1) {
            error("In the first move all used letters must be from your tiles.");
            return;
        }
        // check if word can be placed anywhere on the board
        if(board->firstMove == 0 && checkCreatedWord(board->board_tiles, *player) > 0) {
            error("This word can't be placed anywhere on the board with your letters.");
            return;
        }
        status = positionWord(board, player);       // position the word within the board, enter to confirm
        if (status == 0x0d) {
            placeWord(board, player);        // place a word and check if it can be there
        }
    }
}

EXTERNC
void takeLetters(board_status_t *board, player_t *player) {
    if (board->remaining_letters > 0) {         // check if there are letters left in the pool
        for (int i = 0; i < PLAYER_TILES; ++i) {
            // take only if player's tile is empty, and there are still letter in the pool
            if (player->tiles[i].letter == EMPTY && board->remaining_letters > 0) {
                // take a letter from the end of the pool
                player->tiles[i].letter = board->pool[board->remaining_letters - 1];
                board->remaining_letters--;
            }
        }
    }
}

EXTERNC
void exchangeTiles(board_status_t *board, player_t *player) {
    chooseTiles(board, player);     // player choose with 1-7 (7 is default equality of PLAYER_TILES)
    int count = 0;      // number of tiles exchanged
    for (int i = 0; i < PLAYER_TILES; ++i) {    // check which letters are marked and change them
        if (player->tiles[i].used == 1) {
            swapChars(&(player->tiles[i].letter), &(board->pool[board->remaining_letters-1 - count]));
            ++count;
        }
    }
    // randomize letters which came back to the pool
    for (int i = 0, random; i < count; ++i) {
        random = rand () % board->remaining_letters;
        swapPoolElements(board->pool, random, board->remaining_letters-1 - i);
    }
}

EXTERNC
int endOfGame(player_t player, board_status_t board) {
    for (int i = 0; i < PLAYER_TILES; ++i) {
        if (player.tiles[i].letter != EMPTY) {
            return 0;
        }
    }
    displayEnd(board);
    return 1;
}