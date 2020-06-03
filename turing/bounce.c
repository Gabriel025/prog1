#include <unistd.h>
#include <ncurses.h>

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
        if(pos_x > cols - 1) pos_x = cols - 1;
        if(pos_y > rows - 1) pos_y = rows - 1;

        if(pos_x < 1) vel_x *= -1;
        if(pos_y < 1) vel_y *= -1;
        if(pos_x >= cols - 1) vel_x *= -1;
        if(pos_y >= rows - 1) vel_y *= -1;


        clear();

        mvaddch(pos_y, pos_x, 'O');

        refresh();
        usleep(100000);
    }

    endwin();

    return 0;
}
