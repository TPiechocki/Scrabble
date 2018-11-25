//
// Created by Tomasz Piechocki on 23/11/2018.
//
// Defininitions of consts and some crucial functions e.g. error window
//

#ifndef SCRABBLE_CORE_H
#define SCRABBLE_CORE_H

#define BOARD_PADDING 2 // all side board padding
#define BOARD_SIZE 15   // vertical and horizontal
#define BOARD_LEFT 0    // 1 for board on left and legend on right, 0 for inverse
#if BOARD_LEFT == 0         // board and legend x positioning
#define LEGEND_POSITION 48
#define BOARD_POSITION 1
#else
#define LEGEND_POSITION 2
    #define BOARD_POSITION 60
#endif
#define PlAYER_TILES 7
#define EMPTY 0

#ifdef __cplusplus
extern "C" {
#endif

int boardXPosition(int console_position_x);     // compute coordinates of cursor relative to board
int boardYPosition(int console_position_y);

void error(const char *info);          // error window with information included in call


#ifdef __cplusplus
}
#endif
#endif //SCRABBLE_CORE_H
