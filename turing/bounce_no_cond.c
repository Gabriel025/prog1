#include <unistd.h>
#include <ncurses.h>
#include <math.h>

int is_within_bounds(int n, int max);

int main(int argc, char **argv)
{
    initscr();
    noecho();
    curs_set(0);

    int rows, cols, pos_x, pos_y, vel_x, vel_y;

    pos_x = pos_y = 0;
    vel_x = vel_y = 1;

    while(TRUE)
    {
        pos_x += vel_x;
        pos_y += vel_y;

        getmaxyx(stdscr, rows, cols);
        pos_x %= cols;
        pos_y %= rows;

        //mvprintw(0, 0, "pos_x: is_within_bounds(%d, %d): %d", pos_x, cols - 1, is_within_bounds(pos_x, cols - 1));
        //mvprintw(1, 0, "pos_y: is_within_bounds(%d, %d): %d", pos_y, rows - 1, is_within_bounds(pos_y, rows - 1));
        vel_x *= is_within_bounds(pos_x, cols - 1);
        vel_y *= is_within_bounds(pos_y, rows - 1);


        clear();

        mvaddch(pos_y, pos_x, 'O');

        refresh();
        usleep(100000);
    }

    endwin();

    return 0;
}

//returns -1 if n<=0 or n>=max, 1 otherwise
int is_within_bounds(int n, int max)
{
    int upper = (n / max) * -2 + 1;
    int lower = ((max - n) / max) * -2 + 1;

    return upper * lower;
}
