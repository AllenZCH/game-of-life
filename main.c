#include <string.h>
#include <curses.h>

int side = 40;
bool array[40][40] = {0};

int initial(){
	clear();
	for(int i = 1; i < side + 1; ++i) {
		mvprintw(0, 2 * i - 1, "--");
		mvprintw(side + 1, 2 * i - 1, "--");
		mvprintw(i, 0, "|");
		mvprintw(i, 2 * side + 1, "|");
	}
	mvprintw(0, 0, "+");
	mvprintw(0, 2 * side + 1, "+");
	mvprintw(side + 1, 0, "+");
	mvprintw(side + 1, 2 * side + 1, "+");

	for (int i = 0; i < side; ++i) {
		for (int j = 0; j < side; ++j) {
			if (array[i][j]) {
				mvprintw(i + 1, 2 * j + 1, "[");
				mvprintw(i + 1, 2 * j + 2, "]");
			}
			else {
				mvprintw(i + 1, 2 * j + 1, " ");
				mvprintw(i + 1, 2 * j + 2, " ");
			}
		}
	}
	
	curs_set(1);
	int c, i = 0, j = 0;
	move(1, 1);
	while (1) {
		c = getch();
		switch (c) {
			case 'm':
				curs_set(0);
				return 1;
			case 'j':
				i < side - 1 && move(++i + 1, 2 * j + 1);
				break;
			case 'k':
				i != 0 && move(--i + 1, 2 * j + 1);
				break;
			case 'h':
				j != 0 && move(i + 1, 2 * --j + 1);
				break;
			case 'l':
				j < side - 1 && move(i + 1, 2 * ++j + 1);
				break;
			case 'c':
				array[i][j] = !array[i][j];
				mvprintw(i + 1, 2 * j + 1, array[i][j] ? "[" : " ");
				mvprintw(i + 1, 2 * j + 2, array[i][j] ? "]" : " ");
				move(i + 1, 2 *j + 1);
				break;
		}
	}
}

bool revive(int i, int j){
	int k, l, m, n, a = 0;
	if (i == 0) { k = i; }
	else { k = i - 1; }
	if (i + 1 == side) { l = i + 1; }
	else { l = i + 2; }
	if (j == 0) { m = j; }
	else { m = j - 1; }
	if (j + 1 == side) { n = j + 1; }
	else { n = j + 2; }
	for (int r = k; r < l; ++r) {
		for (int s = m; s < n; ++s) {
			if (array[r][s]) { ++a; }
		}
	}
	a -= array[i][j];
	if (a == 3) { return true; }
	else { return false; }
}

bool doom(int i, int j){
	int k, l, m, n, a = 0;
	if (i == 0) { k = i; }
	else { k = i - 1; }
	if (i + 1 == side) { l = i + 1; }
	else { l = i + 2; }
	if (j == 0) { m = j; }
	else { m = j - 1; }
	if (j + 1 == side) { n = j + 1; }
	else { n = j + 2; }
	for (int r = k; r < l; ++r) {
		for (int s = m; s < n; ++s) {
			if (array[r][s]) { ++a; }
		}
	}
	a -= array[i][j];
	if (a < 2 || a > 3) { return true; }
	else { return false; }
}

int evolve(){
	clear();
	for(int i = 1; i < side + 1; ++i) {
		mvprintw(0, 2 * i - 1, "--");
		mvprintw(side + 1, 2 * i - 1, "--");
		mvprintw(i, 0, "|");
		mvprintw(i, 2 * side + 1, "|");
	}
	mvprintw(0, 0, "+");
	mvprintw(0, 2 * side + 1, "+");
	mvprintw(side + 1, 0, "+");
	mvprintw(side + 1, 2 * side + 1, "+");

	int c;
	while(1) {
		for (int i = 0; i < side; ++i) {
			for (int j = 0; j < side; ++j) {
				if (array[i][j]) {
					mvprintw(i + 1, 2 * j + 1, "[");
					mvprintw(i + 1, 2 * j + 2, "]");
				}
				else {
					mvprintw(i + 1, 2 * j + 1, " ");
					mvprintw(i + 1, 2 * j + 2, " ");
				}
			}
		}
		c = getch();
		if (c == 'm') { return 1; }
		if (c != 'c') { continue; }
		int tmp[side][side];
		for (int i = 0; i < side; ++i) {
			for (int j = 0; j < side; ++j) {
				if (!array[i][j] && revive(i, j)) { tmp[i][j] = 1; }
				else if (array[i][j] && doom(i, j)) { tmp[i][j] = 0; }
				else { tmp[i][j] = array[i][j]; }
			}
		}
		for (int i = 0; i < side; ++i) {
			for (int j = 0; j < side; ++j) { array[i][j] = tmp[i][j]; }
		}
	}
}

int welcome(){
	int stdmaxy = getmaxy(stdscr);
	int stdmaxx = getmaxx(stdscr);
	int stdbegy = getbegy(stdscr);
	int stdbegx = getbegx(stdscr);

	char* welcome_choices[] = {"Run", "Set", "Help", "Quit"};

	clear();
	mvprintw(stdmaxy / 2 - 1, stdmaxx / 2 - 12, "Wellcome to Game of Life!");
	int i = 0;
	attron(A_STANDOUT);
	mvprintw(stdmaxy / 2 + i, stdmaxx / 2 - 12, welcome_choices[i]);
	attroff(A_STANDOUT);
	for (i = 1; i < 4; ++i) { mvprintw(stdmaxy / 2 + i, stdmaxx / 2 - 12, welcome_choices[i]); }
	i = 0;
	int c;
	while (1) {
		c = getch();
		if (c == 'j' && i != 3) {
			mvprintw(stdmaxy / 2 + i, stdmaxx / 2 - 12, welcome_choices[i]);
			++i;
			attron(A_STANDOUT);
			mvprintw(stdmaxy / 2 + i, stdmaxx / 2 - 12, welcome_choices[i]);
			attroff(A_STANDOUT);
		}
		if (c == 'k' && i != 0) {
			mvprintw(stdmaxy / 2 + i, stdmaxx / 2 - 12, welcome_choices[i]);
			--i;
			attron(A_STANDOUT);
			mvprintw(stdmaxy / 2 + i, stdmaxx / 2 - 12, welcome_choices[i]);
			attroff(A_STANDOUT);
		}
		if (c == 'c') {
			switch (i) {
				case 0:
					return 3;
				case 1:
					return 2;
				case 2:
					return 4;
				case 3:
					return 0;
			}
		}
	}
}

int help(){
	clear();
	mvprintw(0, 0, "Press j, k, h, l to select.");
	mvprintw(1, 0, "Press c to confirm / continue.");
	mvprintw(2, 0, "Press m to return menu.");
	mvprintw(4, 0, "Run: Start to evolve.");
	mvprintw(5, 0, "Set: Set initial cells.");
	mvprintw(6, 0, "Help: Show this help page.");
	mvprintw(7, 0, "Quit: Quit the program.");
	int c;
	while (1) {
		c = getch();
		if (c == 'm') { return 1; }
	}
}

int main(int argc, char* argv[]){
	initscr();
	noecho();
	curs_set(0);
	
	int nav = 1;
	while (1) {
		switch (nav) {
			case 0:
				endwin();
				return 0;
			case 1:
				nav = welcome();
				break;
			case 2:
				nav = initial();
				break;
			case 3:
				nav = evolve();
				break;
			case 4:
				nav = help();
				break;
		}
	}
}
