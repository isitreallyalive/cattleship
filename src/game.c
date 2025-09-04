#include "ncurses.h"
#include "game.h"

void board_init(board_t board)
{
    for (int i = 0; i < CELL_COUNT; i++)
    {
        for (int j = 0; j < CELL_COUNT; j++)
        {
            board[i][j] = false;
        }
    }
}

void board_draw(board_t board, vec_t cur, vec_t recent)
{
    // letters across the x-axis
    move(0, 2);
    for (int x = 0; x < CELL_COUNT; ++x)
    {
        printw("%c ", x + 'A');
    }

    for (int y = 0; y < CELL_COUNT; ++y)
    {
        // numbers down the y-axis
        move(y + 1, 0);
        printw("%d ", y + 1);

        // draw cells
        for (int x = 0; x < CELL_COUNT; ++x)
        {
            char ch = board[y][x] ? 'x' : '-';
            vec_t pos = vec_init(x, y);
            bool is_cursor = vec_eq(&cur, &pos);
            bool is_recent = vec_eq(&recent, &pos);
            int pair = (is_cursor && is_recent) ? 3 : is_cursor ? 1
                                                  : is_recent   ? 2
                                                                : 0;
            addch(ch | COLOR_PAIR(pair));
            addch(' ');
        }
    }
}

void board_shoot(board_t *board, vec_t *recent, vec_t pos)
{
    (*board)[pos.y][pos.x] = true;
    *recent = pos;
}