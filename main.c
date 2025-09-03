#include <stdio.h>
#include <ncurses.h>

#define SIZE 8
#define COLOR_BG COLOR_BLACK

#define MOVE(coord, delta, limit)                             \
    do                                                        \
    {                                                         \
        if ((delta) < 0 && game.pos.coord > 0)                \
            game.pos.coord--;                                 \
        else if ((delta) > 0 && game.pos.coord < (limit) - 1) \
            game.pos.coord++;                                 \
    } while (0)

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
    player_t hits[SIZE][SIZE];
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
static bool pos_eq(const pos_t *p1, const pos_t *p2)
{
    return p1->x == p2->x && p1->y == p2->y;
}

/**
 * Render the board.
 *
 * @param game The current state of the game.
 */
static void render(const game_t *game)
{
    const char symbols[] = {'-', 'x', 'o'};
    const char letters[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    clear();

    // print column letters
    move(0, 2);
    for (int x = 0; x < SIZE; ++x)
    {
        printw("%c ", letters[x]);
    }

    for (int y = 0; y < SIZE; ++y)
    {
        move(y + 1, 0);
        printw("%d ", y + 1);
        for (int x = 0; x < SIZE; ++x)
        {
            pos_t curr = {x, y};
            int color = pos_eq(&game->pos, &curr) ? 1 : pos_eq(&game->recent, &curr) ? 2
                                                                                     : 0;
            addch(symbols[game->hits[y][x]] | COLOR_PAIR(color));
            addch(' ');
        }
        refresh();
    }
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
            game.hits[y][x] = PLAYER_NONE;
    game.curr = PLAYER_ONE;
    game.pos = (pos_t){0, 0};
    game.recent = (pos_t){-1, -1};

    // game loop
    int ch;
    while (1)
    {
        render(&game);
        ch = getch();
        if (ch == 'q')
            break;
        switch (ch)
        {
            // clang-format off
        case KEY_UP:    case 'w':  MOVE(y, -1, SIZE); break;
        case KEY_DOWN:  case 's':  MOVE(y, 1, SIZE);  break;
        case KEY_LEFT:  case 'a':  MOVE(x, -1, SIZE); break;
        case KEY_RIGHT: case 'd':  MOVE(x, 1, SIZE);  break;
            // clang-format on

        case ' ':
            if (game.hits[game.pos.y][game.pos.x] == PLAYER_NONE)
            {
                game.hits[game.pos.y][game.pos.x] = game.curr;
                game.recent = game.pos;
                game.curr = (game.curr == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
            }
            break;
        }
    }

    // teardown
    endwin();
    return 0;
}