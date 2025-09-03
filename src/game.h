#pragma once
#include "util/pos.h"

#define BOARD_SIZE 8

typedef bool board_t[BOARD_SIZE][BOARD_SIZE];

/**
 * Initialise the game board by setting all cells to false.
 * 
 * @param board The game board to initialise.
 */
void board_init(board_t board);

typedef struct game
{
    pos_t cur; // the position of the cursor
    board_t p1_shot; // where has player 1 shot?
    board_t p2_shot; // where has player 2 shot?
} game_t;