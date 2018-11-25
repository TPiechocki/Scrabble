#include<stdio.h>
#include"conio2.h"
#include"display/display.h"

/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */

// set a default settings on start or new game
void defaultSettings(board_status_t *board, player_t *player);

int main() {

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

        //legend
        displayLegend(board_status);

        // board
        displayBorder();       // display border of a board
        displayBoard(&board_status);
        displayTiles(player.tiles, sizeof(player.tiles) / sizeof(player.tiles[0]));
                // display tiles in player's hand

        // cursor
        gotoxy(board_status.x, board_status.y);
        textcolor(board_status.text_color);
        textbackground(board_status.background_color);
        putch('*');         // draw a star(cursor)

        // key action
        board_status.zero = 0;
        board_status.ch = getch();

        switch (board_status.ch) {
            case 0:
                board_status.zero = 1;              // if this is the case then we read
                board_status.ch = getch();          // the next code knowing that this
                switch (board_status.ch) {           // this is an arrow
                    case 0x48:
                        (boardYPosition(board_status.y) > 1)?board_status.y--:NULL;
                        break;
                    case 0x50:
                        (boardYPosition(board_status.y) < BOARD_SIZE)?board_status.y++:NULL;
                        break;
                    case 0x4b:
                        (boardXPosition(board_status.x) > 1)?board_status.x--:NULL;
                        break;
                    case 0x4d:
                        (boardXPosition(board_status.x) < BOARD_SIZE)?board_status.x++:NULL;
                        break;
                    default:break;
                }
                break;
            case 'i':
                player.letter = (char)getch();
                insertLetter(&board_status, &player);
                break;
            case 'n':
                defaultSettings(&board_status, &player);
                break;
            case ' ':
                board_status.text_color = (board_status.text_color + 1) % 16;
                break;
            case 0x0d:      // "enter" key
                board_status.background_color = (board_status.background_color + 1) % 16;
                break;
            default:break;
        }
    } while (board_status.ch != 'q');

    _setcursortype(_NORMALCURSOR);      // show the cursor so it will be
                                        // visible after the program ends
    return 0;
}

void defaultSettings(board_status_t *board, player_t *player) {
    board->text_color = WHITE;
    board->background_color = BLACK;
    board->x = boardXStart();
    board->y = boardYStart();
    emptyBoard(board);
    *player = {{'A', 'A', 'O', 'C', 'D', 'G', 'T'}};
}
