#include <stdio.h>
#include <ncurses.h>

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

int main() {
    // setup
    initscr();
    curs_set(0);

    // color support
    if (has_colors()) {
        start_color();
        use_default_colors();
        init_pair(1, COLOR_WHITE, COLOR_RED);
    }

    printwc("hello world", 1);
    getch();

    // cleanup
    endwin();
    return 0;
}