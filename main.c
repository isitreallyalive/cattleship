#include <stdio.h>
#include <ncurses.h>

#define SIZE 8

enum tile
{
    TILE_EMPTY
};
typedef enum tile tile_t;

struct pos
{
    int x;
    int y;
};
typedef struct pos pos_t;

void render(tile_t board[SIZE][SIZE], pos_t pos)
{
    clear();
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
        {
            int color = (pos.x == j && pos.y == i) ? 1 : 0;
            addch('-' | COLOR_PAIR(color));
            addch(' ');
            if (j == SIZE - 1)
                move(i + 1, 0);
        }
    refresh();
}

int main()
{
    // init
    initscr();
    curs_set(0);
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_WHITE);
    }
    keypad(stdscr, TRUE);

    tile_t board[SIZE][SIZE] = {0};
    pos_t pos = {0, 0};

    // game loop
    int ch;
    while (1)
    {
        render(board, pos);
        ch = getch();
        if (ch == 'q')
            break;
        if (ch == KEY_UP && pos.y > 0)
            pos.y--;
        if (ch == KEY_DOWN && pos.y < SIZE - 1)
            pos.y++;
        if (ch == KEY_LEFT && pos.x > 0)
            pos.x--;
        if (ch == KEY_RIGHT && pos.x < SIZE - 1)
            pos.x++;
    }

    // teardown
    endwin();
    return 0;
}