//
// Created by Tomasz Piechocki on 23/11/2018.
//
// Defininitions of consts and some crucial functions e.g. error window
//

#ifndef SCRABBLE_CORE_H
#define SCRABBLE_CORE_H

#define BOARD_PADDING 2 // all side board padding
#define BOARD_SIZE 15   // vertical and horizontal, must be uneven number
#define MIDDLE_TILE (BOARD_SIZE/2 + 1)  // coordinates of middle tile relative to board
#define BOARD_LEFT 1    // 1 for board on left and legend on right, 0 for inverse
#if BOARD_LEFT == 0         // board and legend x positioning
    #define LEGEND_POSITION 48
    #define BOARD_POSITION 1
#else
    #define LEGEND_POSITION 2
    #define BOARD_POSITION 40
#endif
#define PLAYER_TILES 7      // amount of tiles in hand
#define EMPTY 0         // empty tile
// pool content
#define AMOUNT_OF_A 9
#define AMOUNT_OF_B 2
#define AMOUNT_OF_C 2
#define AMOUNT_OF_D 4
#define AMOUNT_OF_E 12
#define AMOUNT_OF_F 2
#define AMOUNT_OF_G 3
#define AMOUNT_OF_H 2
#define AMOUNT_OF_I 9
#define AMOUNT_OF_J 1
#define AMOUNT_OF_K 1
#define AMOUNT_OF_L 4
#define AMOUNT_OF_M 2
#define AMOUNT_OF_N 6
#define AMOUNT_OF_O 8
#define AMOUNT_OF_P 2
#define AMOUNT_OF_Q 1
#define AMOUNT_OF_R 6
#define AMOUNT_OF_S 4
#define AMOUNT_OF_T 6
#define AMOUNT_OF_U 4
#define AMOUNT_OF_V 2
#define AMOUNT_OF_W 2
#define AMOUNT_OF_X 1
#define AMOUNT_OF_Y 2
#define AMOUNT_OF_Z 1
#define AMOUNT_OF_BLANK 2
#define BLANK -1
// direction of arrows
enum{
    UP=-4,
    DOWN,
    LEFT,
    RIGHT
};
#ifdef __cplusplus
extern "C" {
#endif

// count all letters
const int AMOUNT_ALL_LETTERS =  AMOUNT_OF_A + AMOUNT_OF_B + AMOUNT_OF_C + AMOUNT_OF_D + AMOUNT_OF_E + AMOUNT_OF_F +
                                AMOUNT_OF_G + AMOUNT_OF_H + AMOUNT_OF_I + AMOUNT_OF_J + AMOUNT_OF_K + AMOUNT_OF_L +
                                AMOUNT_OF_M + AMOUNT_OF_N + AMOUNT_OF_O + AMOUNT_OF_P + AMOUNT_OF_Q + AMOUNT_OF_R +
                                AMOUNT_OF_S + AMOUNT_OF_T + AMOUNT_OF_U + AMOUNT_OF_V + AMOUNT_OF_W + AMOUNT_OF_X +
                                AMOUNT_OF_Y + AMOUNT_OF_Z + AMOUNT_OF_BLANK;

// status about every tile is stored like this
typedef struct {
    int tile;       // EMPTY or letter
    int bonus;      // EMPTY, negative for word bonus or positive for letter bonus
} board_tile_t;
// status of many elements about board stored here
typedef struct {
    int firstMove;  // 0 if it's not first move, 1 if it's first move and must be placed in middle
    int ch;         // key code
    int cursor_text_color;     // colors for cursor
    int cursor_background_color;
    int zero;       // check whether key has two character code
    int x;          // position of cursor in terminal
    int y;
    int xBoard;     // position of cursor in board
    int yBoard;
    board_tile_t board_tiles[BOARD_SIZE][BOARD_SIZE];
    char pool[AMOUNT_ALL_LETTERS];
    int remaining_letters;
} board_status_t;

void swapChars(char *a, char *b);     // swap values of two char elements

int readArrow(int ch);      // read arrow direction, return UP, DOWN, LEFT or RIGHT
void moveCursor(board_status_t *board, int dir);

// compute coordinates of cursor relative to board
void boardPosition(board_status_t *board);

// get coordinate of cursor relative to the board
int boardXPosition(int conPos);
int boardYPosition(int conPos);

void error(const char *info);          // error window with information included in call

// functions for inserting word
char toUpper(char letter);          // convert lower case to upper case and check if it's actually wanted char
    // return 1 if it's not letter, enter or escape; for rest just return a character

void createPool(char pool[]);     // create a random pool

#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_CORE_H
