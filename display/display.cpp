//
// Created by Tomasz Piechocki on 20/11/2018.
//

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include"../conio2.h"
#include"display.h"
#include "display.h"


#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC    extern "C"
#else
#define EXTERNC
#endif

EXTERNC
void displayLegend(board_status_t board) {
    int count = 2;      // increment on every new line
    char txt[32];
    gotoxy(LEGEND_POSITION, count++);
    cputs("Tomasz Piechocki, 175690");
    gotoxy(LEGEND_POSITION, count++);
    cputs("Implemented: a, b, c, d, e, f, g, h, i");
    count++;

    gotoxy(LEGEND_POSITION, count++);
    cputs("arrows    = move cursor");
    gotoxy(LEGEND_POSITION, count++);
    cputs("q         = exit");
    gotoxy(LEGEND_POSITION, count++);
    cputs("n         = new game");
    gotoxy(LEGEND_POSITION, count++);
    cputs("enter     = confirm a move");
    gotoxy(LEGEND_POSITION, count++);
    cputs("esc       = cancel a move");
    gotoxy(LEGEND_POSITION, count++);
    cputs("i         = insert word");
    gotoxy(LEGEND_POSITION, count++);
    cputs("backspace = delete last letter");
    gotoxy(LEGEND_POSITION, count++);
    cputs("o         = change word orientation");
    gotoxy(LEGEND_POSITION, count++);
    cputs("w         = exchange tiles");
    gotoxy(LEGEND_POSITION, count++);
    cputs("1-7       = choose tiles to exchange");
	gotoxy(LEGEND_POSITION, count++);
	cputs("f         = fix after console resize");
    gotoxy(LEGEND_POSITION, count++);
    cputs("s         = save a game");
    gotoxy(LEGEND_POSITION, count++);
    cputs("l         = load a game");
    count++;

    // for now just for one player
    gotoxy(LEGEND_POSITION, count++);
    cputs("Player's points: ");
    sprintf(txt, "%d", board.points[0]);
    cputs(txt);
    count++;


    gotoxy(LEGEND_POSITION, count++);
    sprintf(txt, "remaining letters: %d", board.remaining_letters);
    cputs(txt);
    gotoxy(LEGEND_POSITION, count++);
    sprintf(txt, "actual position: (%2d,%2d)", board.xBoard, board.yBoard);
    cputs(txt);
    gotoxy(LEGEND_POSITION, count++);
    if (board.zero) sprintf(txt, "key code: 0x00 %d", board.ch);    //code of last pressed key
    else sprintf(txt, "key code: 0x%02x", board.ch);
    cputs(txt);

}

EXTERNC
void bonusDescription(void) {
    int count = 5;
    gotoxy(BOARD_POSITION + 3*BOARD_PADDING + BOARD_SIZE, count++);
    textbackground(MAGENTA);
    cputs(" 2x word bonus   ");
    gotoxy(BOARD_POSITION + 3*BOARD_PADDING + BOARD_SIZE, count++);
    textbackground(LIGHTRED);
    cputs(" 3x word bonus   ");
    gotoxy(BOARD_POSITION + 3*BOARD_PADDING + BOARD_SIZE, count++);
    textbackground(CYAN);
    cputs(" 2x letter bonus ");
    gotoxy(BOARD_POSITION + 3*BOARD_PADDING + BOARD_SIZE, count);
    textbackground(LIGHTBLUE);
    cputs(" 3x letter bonus ");

    textattr(DEFAULT_COLOR);
}

EXTERNC
int boardXStart(void) {
    return BOARD_POSITION + BOARD_PADDING + MIDDLE_TILE;
}

EXTERNC
int boardYStart(void) {
    return BOARD_PADDING + MIDDLE_TILE;
}

EXTERNC
void displayBorder(void){
    char txt[3];
    for (int i = -1; i <= BOARD_SIZE + 2; i++) {
        for (int j = -1; j <= BOARD_SIZE + 2; j++) {
            if ((i <= 0 || i >= BOARD_SIZE + 1) || (j <= 0 || j >= BOARD_SIZE + 1)) {
                gotoxy(j + BOARD_PADDING + BOARD_POSITION, i + BOARD_PADDING);
                textcolor(LIGHTMAGENTA);
                // write ABCD...
                if ((i == 0 || i == BOARD_SIZE + 1) && j > 0 && j <= BOARD_SIZE)
                    putch('A' + j - 1);
                    // write 1234...
                else if (j == -1 && i > 0 && i <= BOARD_SIZE) {
                    sprintf(txt, "%2d", i);
                    cputs(txt);
                }
                else if (j == BOARD_SIZE + 1 && i > 0 && i <= BOARD_SIZE) {
                    sprintf(txt, "%-2d", i);
                    cputs(txt);
                }
            }
        }
    }
}

EXTERNC
void displayBoard(const board_status_t board) {
    textattr(DEFAULT_COLOR);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            gotoxy(i+BOARD_PADDING+BOARD_POSITION+1, j+BOARD_PADDING+1);
            // set background color for bonuses
            switch (board.board_tiles[i][j].bonus) {
                case -3:        // 3x word bonus
                    textbackground(LIGHTRED);
                    break;
                case -2:        // 2x word bonus
                    textbackground(MAGENTA);
                    break;
                case 2:         // 2x letter bonus
                    textbackground(CYAN);
                    break;
                case 3:         // 3x letter bonus
                    textbackground(LIGHTBLUE);
                    break;
                default:
                    textbackground(BLACK);
                    break;
            }
            switch (board.board_tiles[i][j].tile) {
                case EMPTY:
                    putch(' ');
                    break;
                default:
                    putch(board.board_tiles[i][j].tile);
            }
        }
    }
    if (board.firstMove == 1) {         // display MIDDLE OF BOARD if it's first move
        gotoxy(MIDDLE_TILE + BOARD_PADDING + BOARD_POSITION, MIDDLE_TILE + BOARD_PADDING);
        textattr(WHITE * 16 + BLACK);
        putch('+');
        textattr(DEFAULT_COLOR);
    }
}

EXTERNC
void displayTiles(const player_tile_t tiles[]) {
    for (int i = 0; i < PLAYER_TILES; ++i) {
        gotoxy(BOARD_POSITION + BOARD_PADDING + 2*i + 2, 2*BOARD_PADDING + BOARD_SIZE + 2);
        textattr(WHITE*16 + BLACK);
        if (tiles[i].letter == BLANK)
            putch('?');
        else
            putch(tiles[i].letter);
        gotoxy(BOARD_POSITION + BOARD_PADDING + 2*i + 2, 2*BOARD_PADDING + BOARD_SIZE + 2 + 1);
        textattr(DEFAULT_COLOR);
        if (tiles[i].letter == BLANK) {
            putch('?');     // we don't know blank value as it takes value of letter it replaces
        }
        else {
            if (all_letters[tiles[i].letter - 'A'][LETTER_POINTS] == 10)
                putch('X');     // X is as 10 points
            else
                putch(all_letters[tiles[i].letter - 'A'][LETTER_POINTS] + '0');
        }
    }
}

EXTERNC
void displayTilesExchange(const player_tile_t tiles[]) {
    for (int i = 0; i < PLAYER_TILES; ++i) {
        gotoxy(BOARD_POSITION + BOARD_PADDING + 2*i + 2, 2*BOARD_PADDING + BOARD_SIZE + 2);
        if (tiles[i].used != 0)
            textattr(BROWN*16 + BLACK);
        else
            textattr(WHITE*16+BLACK);
        if (tiles[i].letter == BLANK)
            putch('?');
        else
            putch(tiles[i].letter);
        gotoxy(BOARD_POSITION + BOARD_PADDING + 2*i + 2, 2*BOARD_PADDING + BOARD_SIZE + 3);
        textattr(DEFAULT_COLOR);
        putch('1' + i);
    }
}

EXTERNC
void displayWordCreate(const player_t player) {
    for (int i = 0; i <= BOARD_SIZE ; ++i) {
        gotoxy(5+i,25);
        putch(' ');
    }
    gotoxy(5,25);
    for (int i = 0; player.word[i] != '\0'; ++i) {
        if (player.word_status[i] == 0)
            textattr(RED*16 + WHITE);
        else if (player.word_status[i] == 1)
            textattr(GREEN*16 + WHITE);
        putch(player.word[i]);
    }
    textattr(DEFAULT_COLOR);
}

EXTERNC
void displayWordInsert(board_status_t *board, player_t *player) {
    int length = strlen(player->word);
    gotoxy(board->x, board->y);
    if (player->word_orientaion == HORIZONTAL) {
        for (int i = 0; player->word[i] != '\0'; ++i) {
            while (boardXPosition(board->x) + length > BOARD_SIZE + 1)
                board->x--;
            boardPosition(board);
            if (board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile == EMPTY ||
                board->board_tiles[board->xBoard+i-1][board->yBoard-1].tile == player->word[i]) {
                textattr(GREEN * 16 + WHITE);
            }
            else {
                textattr(RED * 16 + WHITE);
            }
            gotoxy(board->x+i, board->y);
            putch(player->word[i]);
        }
    }
    else {
        for (int i = 0; player->word[i] != '\0'; ++i) {
            while(boardYPosition(board->y) + length > BOARD_SIZE+1 )
                board->y--;
            boardPosition(board);
            if (board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile == EMPTY ||
                board->board_tiles[board->xBoard-1][board->yBoard+i-1].tile == player->word[i]) {
                textattr(GREEN * 16 + WHITE);
            }
            else {
                textattr(RED * 16 + WHITE);
            }
            gotoxy(board->x, board->y + i);
            putch(player->word[i]);
        }
    }
    boardPosition(board);
    textattr(BLACK * 16 + WHITE);
}

EXTERNC
void displayAll(const board_status_t board, const player_t player) {
    displayLegend(board);
    bonusDescription();
    displayBorder();
    displayBoard(board);
    displayTiles(player.tiles);

}

