#include "board.h"
#include "player.h"
#include <ncurses.h>

#define CELL_HIT 'x'
#define CELL_MISS 'o'
#define CELL_EMPTY '.'

void board_draw(const board_t board, const vec_t cur) {
  // letters across the x-axis
  move(0, 2);
  for (int x = 0; x < CELL_COUNT; ++x) {
    printw("%c ", x + 'A');
  }

  for (int y = 0; y < CELL_COUNT; ++y) {
    // numbers down the y-axis
    move(y + 1, 0);
    printw("%d ", y + 1);

    for (int x = 0; x < CELL_COUNT; ++x) {
      // draw cell
      // todo: check if it was a hit or a miss
      bool is_shot = board[y][x];
      char ch = is_shot ? CELL_HIT : CELL_EMPTY;

      vec_t pos = VEC(x, y);
      bool is_cursor = vec_eq(&cur, &pos);
      int pair = is_cursor ? 1 : 0;
      int attrs = COLOR_PAIR(pair);

      addch(ch | attrs);
      addch(' ');
    }
  }
}

void board_shoot(vec_t pos, board_t *shots) { (*shots)[pos.y][pos.x] = true; }