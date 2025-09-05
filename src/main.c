#include "struct/board.h"
#include "struct/player.h"
#include <ncurses.h>

#define COLOR_BG COLOR_BLACK
#define COLOR_FG COLOR_WHITE

int main() {
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
    board_draw(player->shots, player->cur);
    refresh();

    // handle controls
    ch = getch();
    if (ch == 'q')
      break;
    switch (ch) {
      // clang-format off
	// movement
	case KEY_UP:    case 'w': vec_add(&player->cur, 0, -1); break;                              break;
	case KEY_DOWN:  case 's': vec_add(&player->cur, 0, 1);  break;                               break;
	case KEY_LEFT:  case 'a': vec_add(&player->cur, -1, 0); break;                              break;
	case KEY_RIGHT: case 'd': vec_add(&player->cur, 1, 0);  break;                               break;
      // clang-format on
    case ' ': {
      board_shoot(player->cur, &player->shots);
      player = (player == &p1) ? &p2 : &p1; // switch player
      break;
    }
    }
  }

  // teardown
  endwin();
  return 0;
}