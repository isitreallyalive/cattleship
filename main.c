#include <stdio.h>
#include <ncurses.h>

int main() {
    // setup
    initscr();
    curs_set(0);

    printw("hello world\n");
    getch();

    // cleanup
    endwin();
    return 0;
}