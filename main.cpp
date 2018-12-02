#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"conio2.h"
#include"display/display.h"
#include"game/save.h"
#include"core/dictionary.h"

// set a default settings on start or new game
void defaultSettings(board_status_t *board, player_t *player);

int main(int argc, char* argv[]) {
    dict_word_t *head_dict = NULL;      // head of list
    char dictName[30] = "\0";       // buffer for file name
    for (int i = 0; i < argc; ++i) {    // look for dictionary name in executing command
		if (strcmp(argv[i], "-d") == 0)
			strcpy(dictName, argv[i+1]);
	}
    if (strcmp(dictName, "\0") == 0)    // default directory if other is not pointed
        strcpy(dictName, "479k.txt");

    // create a dictionary, head of list is stored in head_dict
    if (createDictionary(dictName, head_dict) != 0) {
        error("Problem with creating the dictionary. Program will close itself.");
        deleteDictionary(head_dict);    // free the space
        return 1;
    }

    board_status_t board_status;       // structure with board status: key code, colours, zero to check
    board_status.ch = 0; board_status.zero = 0;   // double character code of keys and coordinates of cursor
    player_t player;             // player status with: tiles
    defaultSettings(&board_status, &player);

    // if the program is compiled in pure C, then we need to initialize
    // the library ourselves; __cplusplus is defined only if a C++ compiler
    // is used
#ifndef __cplusplus
    Conio2_Init();
#endif
    settitle("Tomasz, Piechocki, 175690");    // sets window title

    _setcursortype(_NOCURSOR);  // hide the blinking cursor
    do {
        textbackground(BLACK);
        clrscr();               //clear the screen, fill all with spaces
        textcolor(WHITE);

        boardPosition(&board_status);

        // display legend, board and player's tiles
        displayAll(board_status, player);

        // cursor
        gotoxy(board_status.x, board_status.y);
        textcolor(board_status.cursor_text_color);
        textbackground(board_status.cursor_background_color);
        putch('*');         // draw a star(cursor)

        // key action
        board_status.zero = 0;
        board_status.ch = getch();

        switch (board_status.ch) {
            case 0:         // it means one of arrows
                board_status.zero = 1;              // if this is the case then we read
                board_status.ch = readArrow(getch());          // the next code knowing that this
                switch (board_status.ch) {           // this is an arrow
                    case UP:
                        (board_status.yBoard > 1)?board_status.y--:NULL;
                        break;
                    case DOWN:
                        (board_status.yBoard < BOARD_SIZE)?board_status.y++:NULL;
                        break;
                    case LEFT:
                        (board_status.xBoard > 1)?board_status.x--:NULL;
                        break;
                    case RIGHT:
                        (board_status.xBoard < BOARD_SIZE)?board_status.x++:NULL;
                        break;
                    default:break;
                }
                boardPosition(&board_status);
                break;
            case 'i':       // for inserting a word
                insertWord(&board_status, &player);
                takeLetters(&board_status, &player);        // fill letters from pool
                break;
            case 'n':       // new game with start settings
                defaultSettings(&board_status, &player);
				_setcursortype(_NOCURSOR);  // hide the blinking cursor
                break;
            case 'w':       // exchange chosen tiles
                exchangeTiles(&board_status, &player);
                break;
			case 'f':		// fix after console resize
				_setcursortype(_NOCURSOR);  // hide the blinking cursor
				break;
            case 's':		// save a game
                saveGame(&board_status, &player);
                break;
            case 'l':		// load a game
                loadGame(&board_status, &player);
                break;
            default:break;
        }
    } while (board_status.ch != 'q' && endOfGame(player) == 0); // q for exit

    //deleteDictionary(head_dict);        // free space of dictionary
	clrscr();
    _setcursortype(_NORMALCURSOR);      // show the cursor so it will be
                                        // visible after the program ends
    return 0;
}

void defaultSettings(board_status_t *board, player_t *player) {
    board->cursor_text_color = WHITE;
    board->cursor_background_color = BLACK;
    board->x = boardXStart();       // set start position of cursor
    board->y = boardYStart();
    board->firstMove = 1;
    emptyBoard(board);              // empty board with spaces
    createPool(board->pool);        // create a random pool
    board->remaining_letters = AMOUNT_ALL_LETTERS;      // set remaining letters to all
    for (int i = 0; i < PLAYER_TILES; ++i) {    // empty player's tiles
        player->tiles[i].letter = EMPTY;
        player->tiles[i].used = 0;
    }
    for (int i = 0; i < NUMBER_OF_PLAYERS; ++i) {       // set points of players to 0
        board->points[i] = 0;
    }
    board->player = 0;                  // start a player 0
    takeLetters(board, player);         // player takes tiles
    initializeBonuses(board);           // set bonuses on the board
}