#include <ncurses.h>
#include <unistd.h>

#define HEIGHT 32
#define WIDTH 64

void initscreen() {
	initscr();
	noecho();
}

void closescreen() {
	endwin();
}

void draw(int matrix[WIDTH][HEIGHT]) {
	int i, j;
	clear();
	for(i = 0; i < HEIGHT; i++)
		for(j = 0; j < WIDTH; j ++)
			if(matrix[i][j] == 1)
				mvprintw(j, i, "X");
	refresh();
}

int main() {
	initscreen();
	int matrix[WIDTH][HEIGHT] = {0};
	matrix[1][1] = 1;
	matrix[1][2] = 1;	
	draw(matrix);
	sleep(3);
	matrix[1][3] = 1;
	draw(matrix);
	sleep(3);
	closescreen();
	return 0;
}
