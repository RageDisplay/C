#include <ncurses.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
initscr();
keypad(stdscr, TRUE);
noecho();
curs_set(0);
int x1[5];
int y1[5];
int ch;
int x,y,i,j=0;
x = COLS/2;
y = LINES/2;
for(i=0; i<5; i++)
{
	x1[i] = x;
	y1[i] = y-1;
}
initscr();
noecho();
keypad(stdscr, TRUE);
while (ch != 'q')
{
	for (i=0; i<5; i++)
	{
		mvaddch(y1[i],x1[i], '*');
	}
	refresh();
	ch = getch();
	if (j>=4)
	{
		mvaddch(y1[0],x1[0], ' ');
	}
	switch(ch)
	{
	case KEY_UP:
		for(i=0; i<4; i++)
		{
			x1[i]=x1[i+1];
			y1[i]=y1[i+1];
		}
		y1[4]=(y1[4]+LINES-1)%LINES;
		break;
	case KEY_DOWN:
		for(i=0; i<4; i++)
		{
			x1[i]=x1[i+1];
			y1[i]=y1[i+1];
		}
		y1[4]=(y1[4]+1)%LINES;
		break;
	case KEY_LEFT:
		for(i=0; i<4; i++)
		{
			x1[i]=x1[i+1];
			y1[i]=y1[i+1];
		}
		x1[4]=(x1[4]+COLS-1)%COLS;
		break;
	case KEY_RIGHT:
		for(i=0; i<4;i++)
		{
			x1[i]=x1[i+1];
			y1[i]=y1[i+1];
		}
		x1[4]=(x1[4]+1)%COLS;
		break;
	default:
		break;
	}
	if(j<5)
		j++;
}
endwin();
return 0;
}
