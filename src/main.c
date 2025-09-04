#include <ncurses.h>
#include "game.h"

#define COLOR_BG COLOR_BLACK
#define COLOR_FG COLOR_WHITE

int main()
{
    // initialise ncurses
    initscr();
    curs_set(0);

    if (has_colors())
    {
        start_color();
        init_pair(0, COLOR_FG, COLOR_BG);
        init_pair(1, COLOR_BG, COLOR_FG);
    }

    // initialise game state
    game_t state;
    state.cur = vec_init(0, 0);
    board_init(state.p1_shot);
    board_init(state.p2_shot);

    // game loop
    int ch;
    while (true)
    {
        // draw ui
        clear();
        board_draw(state.p1_shot, state.cur);
        refresh();

        // handle controls
        ch = getch();
        if (ch == 'q')
            break;
        switch (ch)
        {
            // clang-format off
            case KEY_UP: case 'w': vec_add(&state.cur, 0, -1); break;
            case KEY_DOWN: case 's': vec_add(&state.cur, 0, 1); break;
            case KEY_LEFT: case 'a': vec_add(&state.cur, -1, 0); break;
            case KEY_RIGHT: case 'd': vec_add(&state.cur, 1, 0); break;
            // clang-format on
        }
    }

    // teardown
    endwin();
    return 0;
}