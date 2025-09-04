#pragma once
#include "util/vec.h"

#define CELL_COUNT 8
#define BOARD_SIZE (CELL_COUNT * 2 + 1)

typedef bool board_t[CELL_COUNT][CELL_COUNT];

typedef struct game
{
    vec_t cur;       // the position of the cursor
    vec_t recent;    // the most recent position that was shot at
    board_t p1_shot; // where has player 1 shot?
    board_t p2_shot; // where has player 2 shot?
} game_t;

/**
 * Initialise the game board by setting all cells to false.
 *
 * @param board A pointer to the game board to initialise.
 */
void board_init(board_t *board);

/**
 * Draw a board to the screen.
 *
 * @param board The game board to draw.
 * @param cur The current cursor position.
 * @param recent The most recent shot position.
 */
void board_draw(const board_t board, const vec_t cur, const vec_t recent);

/**
 * Mark a position on the board as shot.
 *
 * @param board Pointer to the game board.
 * @param recent Pointer to the most recent shot position.
 * @param pos The position to mark as shot.
 */
void board_shoot(board_t *board, vec_t *recent, const vec_t pos);