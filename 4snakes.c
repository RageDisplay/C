#include <ncurses.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
initscr();
keypad(stdscr, TRUE);
noecho();
curs_set(0);
int x1[5],x2[5],x3[5],x4[5];
int y1[5],y2[5],y3[5],y4[5];
int ch;
int x,y,i,j=0;
x = COLS/2;
y = LINES/2;
for(i=0; i<5; i++)
{
	x1[i] = x;
	y1[i] = y-1;
	x2[i] = x+1;
	y2[i] = y;
	x3[i] = x;
	y3[i] = y+1;
	x4[i] = x-1;
	y4[i] = y;
}
initscr();
noecho();
keypad(stdscr, TRUE);
while (ch != 'q')
{
	for (i=0; i<5; i++)
	{
		mvaddch(y1[i],x1[i], '*');
		mvaddch(y2[i],x2[i], '*');
		mvaddch(y3[i],x3[i], '*');
		mvaddch(y4[i],x4[i], '*');
	}
	refresh();
	ch = getch();
	if (j>=4)
	{
		mvaddch(y1[0],x1[0], ' ');
		mvaddch(y2[0],x2[0], ' ');
		mvaddch(y3[0],x3[0], ' ');
		mvaddch(y4[0],x4[0], ' ');
	}
	switch(ch)
	{
	case KEY_UP:
		for(i=0; i<4; i++)
		{
			x1[i]=x1[i+1];
			x2[i]=x2[i+1];
			x3[i]=x3[i+1];
			x4[i]=x4[i+1];
			y1[i]=y1[i+1];
			y2[i]=y2[i+1];
			y3[i]=y3[i+1];
			y4[i]=y4[i+1];
		}
		y1[4]=(y1[4]+LINES-1)%LINES;
		x2[4]=(x2[4]+1)%COLS;
		y3[4]=(y3[4]+1)%LINES;
		x4[4]=(x4[4]+COLS-1)%COLS;
		break;
	case KEY_DOWN:
		for(i=0; i<4; i++)
		{
			x1[i]=x1[i+1];
			x2[i]=x2[i+1];
			x3[i]=x3[i+1];
			x4[i]=x4[i+1];
			y1[i]=y1[i+1];
			y2[i]=y2[i+1];
			y3[i]=y3[i+1];
			y4[i]=y4[i+1];
		}
		y3[4]=(y3[4]+LINES-1)%LINES;
		x4[4]=(x4[4]+1)%COLS;
		y1[4]=(y1[4]+1)%LINES;
		x2[4]=(x2[4]+COLS-1)%COLS;
		break;
	case KEY_LEFT:
		for(i=0; i<4; i++)
		{
			x1[i]=x1[i+1];
			x2[i]=x2[i+1];
			x3[i]=x3[i+1];
			x4[i]=x4[i+1];
			y1[i]=y1[i+1];
			y2[i]=y2[i+1];
			y3[i]=y3[i+1];
			y4[i]=y4[i+1];
		}
		y2[4]=(y2[4]+LINES-1)%LINES;
		x3[4]=(x3[4]+1)%COLS;
		y4[4]=(y4[4]+1)%LINES;
		x1[4]=(x1[4]+COLS-1)%COLS;
		break;
	case KEY_RIGHT:
		for(i=0; i<4;i++)
		{
			x1[i]=x1[i+1];
			x2[i]=x2[i+1];
			x3[i]=x3[i+1];
			x4[i]=x4[i+1];
			y1[i]=y1[i+1];
			y2[i]=y2[i+1];
			y3[i]=y3[i+1];
			y4[i]=y4[i+1];
		}
		y4[4]=(y4[4]+LINES-1)%LINES;
		x1[4]=(x1[4]+1)%COLS;
		y2[4]=(y2[4]+1)%LINES;
		x3[4]=(x3[4]+COLS-1)%COLS;
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
