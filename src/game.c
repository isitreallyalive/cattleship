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

void board_draw(board_t board, vec_t cur)
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
            bool pair = vec_eq(&cur, &pos);
            addch(ch | COLOR_PAIR(pair));
            addch(' ');
        }
    }
}