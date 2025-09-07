#include "const.h"
#include "player.h"
#include <ncurses.h>
#include <time.h>

#define COLOR_BG COLOR_BLACK
#define COLOR_FG COLOR_WHITE

static inline int clamp(int val) {
  if (val < 0)
    return 0;
  if (val >= BOARD_SIZE)
    return BOARD_SIZE - 1;
  return val;
}

int main() {
  srand(time(NULL));    // random seed
  initscr();            // initialise ncurses
  curs_set(0);          // hide cursor
  keypad(stdscr, TRUE); // enable arrow keys

  if (has_colors()) {
    start_color();
    init_pair(0, COLOR_FG, COLOR_BG);  // default
    init_pair(1, COLOR_BG, COLOR_FG);  // cursor
    init_pair(2, COLOR_RED, COLOR_BG); // recent
  }

  // initialise game state
  player_t p1 = player_init();
  player_t p2 = player_init();

  // game loop
  int ch;
  player_t *player = &p1;
  while (true) {
    // draw ui
    clear();
    // TODO: draw
    refresh();

    // handle controls
    ch = getch();
    if (ch == 'q')
      break;
    switch (ch) {
      // clang-format off
	// movement
	case KEY_UP:    case 'w': player->cur.y = clamp(player->cur.y - 1); break;
	case KEY_DOWN:  case 's': player->cur.y = clamp(player->cur.y + 1); break;
	case KEY_LEFT:  case 'a': player->cur.x = clamp(player->cur.x - 1); break;
	case KEY_RIGHT: case 'd': player->cur.x = clamp(player->cur.x + 1); break;
      // clang-format on
    case ' ': {
      player = (player == &p1) ? &p2 : &p1; // switch player
      break;
    }
    }
  }

  // teardown
  endwin();
  return 0;
}