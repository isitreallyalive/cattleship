#include <stdio.h>
#include <ncurses.h>

#define SIZE 8

enum tile {
    TILE_EMPTY
};
typedef enum tile tile_t;

struct pos {
    int x;
    int y;
};
typedef struct pos pos_t;

/**
 * Prints a string to the terminal using the specified color pair.
 *
 * @param string The string to print.
 * @param n The color pair number to use.
 */
void printwc(const char *string, int n) {
    attron(COLOR_PAIR(n));
    printw("%s", string);
    attroff(COLOR_PAIR(n));
}

void render(tile_t board[SIZE][SIZE], pos_t selected) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            char c;
            int color = 0;
            if (selected.x == j && selected.y == i) {
                color = 1;
            }

            switch (board[i][j]) {
                case TILE_EMPTY:
                    c = '-';
                    break;
            }

            addch(c | COLOR_PAIR(color));
            addch(' ');
        }
        addch('\n');
    }
}

int main() {
    // --- ncurses ---
    // init
    initscr();
    curs_set(0);

    // color support
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_WHITE);
    }

    // --- game ---
    // populate board
    tile_t board[SIZE][SIZE];
    pos_t selected;
    selected.x = 0;
    selected.y = 0;
    
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = TILE_EMPTY;
        }
    }

    render(board, selected);
    getch();

    // cleanup
    endwin();
    return 0;
}