#include <stdio.h>
#include <ncurses.h>

#define SIZE 8

enum player
{
    PLAYER_NONE,
    PLAYER_ONE,
    PLAYER_TWO
};
typedef enum player player_t;

struct pos
{
    int x;
    int y;
};
typedef struct pos pos_t;

void render(player_t board[SIZE][SIZE], pos_t pos)
{
    clear();
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
        {
            char ch;
            switch (board[i][j]) {
                case PLAYER_NONE:
                    ch = '-';
                    break;
                case PLAYER_ONE:
                    ch = 'x';
                    break;
                case PLAYER_TWO:
                    ch = 'o';
                    break;
            }
            int color = (pos.x == j && pos.y == i) ? 1 : 0;
            addch(ch | COLOR_PAIR(color));
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

    player_t board[SIZE][SIZE] = {PLAYER_NONE};
    player_t current = PLAYER_ONE;
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
        if (ch == ' ' && board[pos.y][pos.x] == PLAYER_NONE)
        {
            board[pos.y][pos.x] = current;
            current = (current == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
        }
    }

    // teardown
    endwin();
    return 0;
}