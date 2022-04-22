#include <ncurses/ncurses.h>
using namespace std;

int main(int argc, char *argv[]) {
    initscr();
    
    int height = 10;
    int width = 20;
    int start_y = 10;
    int start_x = 10;

    WINDOW *win = newwin(height, width, start_y, start_x);
    refresh();
    box(win, 0, 0);
    wprintw(win, "Hello World!");

    wrefresh(win);
    getch();
    endwin();
    return 0;
}
