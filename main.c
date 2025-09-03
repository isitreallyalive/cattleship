#include <stdio.h>
#include <ncurses.h>

#define SIZE 8
#define COLOR_BG COLOR_BLACK

enum player
{
    PLAYER_NONE = 0,
    PLAYER_ONE = 1,
    PLAYER_TWO = 2
};
typedef enum player player_t;

struct pos
{
    int x;
    int y;
};
typedef struct pos pos_t;

struct game
{
    player_t curr;
    player_t board[SIZE][SIZE];
    pos_t pos;
    pos_t recent;
};
typedef struct game game_t;

/**
 * Check if two positions are equal.
 *
 * @param p1 First position.
 * @param p2 Second position.
 * @returns TRUE if the positions are equal, FALSE otherwise.
 */
static bool pos_eq(pos_t p1, pos_t p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

/**
 * Render the board.
 *
 * @param game The current state of the game.
 */
void render(const game_t *game)
{
    clear();
    for (int y = 0; y < SIZE; ++y)
        for (int x = 0; x < SIZE; ++x)
        {
            const char symbols[] = {'-', 'x', 'o'};
            pos_t curr = {x, y};
            int color = pos_eq(game->pos, curr) ? 1 : pos_eq(game->recent, curr) ? 2
                                                                                 : 0;
            addch(symbols[game->board[y][x]] | COLOR_PAIR(color));
            addch(' ');
            if (x == SIZE - 1)
                move(y + 1, 0);
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
        init_pair(1, COLOR_BG, COLOR_WHITE);
        init_pair(2, COLOR_BG, COLOR_YELLOW);
    }
    keypad(stdscr, TRUE);

    game_t game;

    for (int y = 0; y < SIZE; ++y)
        for (int x = 0; x < SIZE; ++x)
            game.board[y][x] = PLAYER_NONE;
    game.curr = PLAYER_ONE;
    game.pos = (pos_t){0, 0};
    game.recent = (pos_t){-1, -1};

    // alias pointers
    pos_t *pos = &game.pos;
    pos_t *recent = &game.recent;
    player_t(*board)[SIZE] = game.board;

    // game loop
    int ch;
    while (1)
    {
        render(&game);
        ch = getch();
        switch (ch)
        {
        case 'q':
            break;
        case KEY_UP:
            if (game.pos.y > 0)
                game.pos.y--;
            break;
        case KEY_DOWN:
            if (game.pos.y < SIZE - 1)
                game.pos.y++;
            break;
        case KEY_LEFT:
            if (game.pos.x > 0)
                game.pos.x--;
            break;
        case KEY_RIGHT:
            if (game.pos.x < SIZE - 1)
                game.pos.x++;
            break;
        case ' ':
            if (game.board[game.pos.y][game.pos.x] == PLAYER_NONE)
            {
                game.board[game.pos.y][game.pos.x] = game.curr;
                game.recent = game.pos;
                game.curr = (game.curr == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
            }
            break;
        }
        if (ch == 'q')
            break;
    }

    // teardown
    endwin();
    return 0;
}