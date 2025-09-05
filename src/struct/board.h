#pragma once
#include "vec.h"

#define CELL_COUNT 8
#define BOARD_SIZE (CELL_COUNT * 2 + 1)

typedef bool board_t[CELL_COUNT][CELL_COUNT];

/**
 * Draw a board to the screen.
 *
 * @param board The game board to draw.
 * @param cur The current cursor position.
 */
void board_draw(const board_t board, const vec_t cur);

/**
 * Mark a position on the board as shot.
 *
 * @param pos The position to shoot at.
 * @param shots The current player's shots board.
 */
void board_shoot(vec_t pos, board_t *shots);