#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <ncurses.h>
#include <pthread.h>
#define n 55

int x[n];
int y[n];
int is_key = 1;
int work_flag = 1;
void handler(int none)
{
  work_flag = 0;
  is_key = 0;
}
typedef struct
{
	int key;
	uint32_t *ptr;
	struct fb_var_screeninfo scr;
} 
snake_struct;
void CoordsChange()
{
	for (int j = 0; j < n - 1; j++)
	{
		x[j] = x[j+1];
		y[j] = y[j+1];
	}
}
void* Snake(void* information)
{
	uint32_t color = 0xFF00FF;
	uint32_t uncolor = 0xE6E6FA;
	snake_struct info = *((snake_struct*)information);
	switch(info.key)
	{
		case KEY_LEFT:
				while(is_key)
				{
					for (int i = 0; i < n; i++)
						info.ptr[y[i] * info.scr.xres_virtual  + x[i]] = uncolor;
					CoordsChange();
					x[n-1] = (x[n-1] + info.scr.yres - 1) % info.scr.yres;
					for (int i = 0; i < n; i++)
						info.ptr[y[i] * info.scr.xres_virtual  + x[i]] = color;
					usleep(10000);
				}
				break;
			case KEY_RIGHT:
				while(is_key)
				{
					for (int i = 0; i < n; i++)
						info.ptr[y[i] * info.scr.xres_virtual  + x[i]] = uncolor;
					CoordsChange();
					x[n-1] = (x[n-1] + 1) % info.scr.yres;
					for (int i = 0; i < n; i++)
						info.ptr[y[i] * info.scr.xres_virtual  + x[i]] = color;
					usleep(10000);
				}
				break;
			case KEY_DOWN:
				while(is_key)
				{
					for (int i = 0; i < n; i++)
						info.ptr[y[i] * info.scr.xres_virtual  + x[i]] = uncolor;
					CoordsChange();
					y[n-1] = (y[n-1] + 1) % info.scr.xres;
					for (int i = 0; i < n; i++)
						info.ptr[y[i] * info.scr.xres_virtual  + x[i]] = color;
					usleep(10000);
				}
				break;
			case KEY_UP:
				while(is_key)
				{
					for (int i = 0; i < n; i++)
						info.ptr[y[i] * info.scr.xres_virtual  + x[i]] = uncolor;
					CoordsChange();
					y[n-1] = (y[n-1] + info.scr.xres - 1) % info.scr.xres;
					if (y[n-1] < 0)
						y[n-1] = y[n-1] + info.scr.xres;
					for (int i = 0; i < n; i++)
						info.ptr[y[i] * info.scr.xres_virtual  + x[i]] = color;
					usleep(10000);
				}
				break;
			default:
				break;
	}	
}
int main(int argc, char *argv[])
{
  int fb;
  struct fb_var_screeninfo info;
  size_t fb_size, map_size, page_size;
  uint32_t *ptr, color;

  signal(SIGINT, handler);
  page_size = sysconf(_SC_PAGESIZE);
  
  if ( 0 > (fb = open("/dev/fb0", O_RDWR))) {
    perror("open");
    return __LINE__;
  }

  if ( (-1) == ioctl(fb, FBIOGET_VSCREENINFO, &info)) {
    perror("ioctl");
    close(fb);
    return __LINE__;
  }

  fb_size = sizeof(uint32_t) * info.xres_virtual * info.yres_virtual;
  map_size = (fb_size + (page_size - 1 )) & (~(page_size-1));

  ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
  if ( MAP_FAILED == ptr ) {
    perror("mmap");
    close(fb);
    return __LINE__;
  }
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  pthread_t snake_thread;
  snake_struct info_snake;
  info_snake.key = KEY_RIGHT;
  info_snake.ptr = ptr;
  info_snake.scr = info;
  for (int i = 0; i < n; i++)
  {
  	x[i] = 0;
  	y[i] = 0;
  }
  while (work_flag)
  {
  	if (pthread_create(&snake_thread, NULL, Snake, (void*)&info_snake))
  	{
  		endwin();
  		fprintf(stderr, "Error with the creaction of the flow");
  		exit(1);
  	}
	do
		info_snake.key = getch();
	while((info_snake.key!=KEY_RIGHT)&&(info_snake.key!=KEY_LEFT)&&(info_snake.key!=KEY_UP)&&(info_snake.key!=KEY_DOWN)&&(work_flag));
  	is_key = 0;
  	if (pthread_join(snake_thread, NULL))
  	{
  		endwin();
  		fprintf(stderr, "Flow couldn't be created");
  		exit(2);
  	}
  	is_key = 1;
 }
 endwin(); 
 munmap(ptr, map_size);
  close(fb);
  return 0;
}
