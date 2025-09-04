#pragma once
#include "util/vec.h"

#define CELL_COUNT 8
#define BOARD_SIZE (CELL_COUNT * 2 + 1)

typedef bool board_t[CELL_COUNT][CELL_COUNT];

typedef struct game
{
    vec_t cur;       // the position of the cursor
    board_t p1_shot; // where has player 1 shot?
    board_t p2_shot; // where has player 2 shot?
} game_t;

/**
 * Initialise the game board by setting all cells to false.
 *
 * @param board The game board to initialise.
 */
void board_init(board_t board);

/**
 * Draw a board to the screen.
 *
 * @param board The game board to draw.
 * @param cur The current cursor position.
 */
void board_draw(board_t board, vec_t cur);