#include <ncurses.h>
#include "game.h"

int main() {
    // initialise ncurses
    initscr();
    curs_set(0);
    
    // initialise game state
    game_t state;
    state.cur = pos_init(0, 0);
    board_init(state.p1_shot);
    board_init(state.p2_shot);

    // teardown
    endwin();
    return 0;
}