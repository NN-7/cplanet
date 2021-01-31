#include <curses.h>
#include <stdio.h>
#define PLANET_WIDTH 8
#define PLANET_HEIGHT 5
#define PALETTE_SIZE 5

int
main (void) {
  initscr ();
  //start_color ();
  cbreak ();
  keypad (stdscr, TRUE);
  nodelay (stdscr, TRUE);
  noecho ();
  clear ();
  int hight, width;
  getmaxyx (stdscr, hight, width);
  int x = 0, y = 0;
  move (2, 2);
  getyx (stdscr, y, x);
  int palette[PALETTE_SIZE] = {'W', 'w', '.', 'F' | A_UNDERLINE, '#'};
  int planet[PLANET_HEIGHT][PLANET_WIDTH] = {{4,4,4,4,4,4,4,4},
                        {1,0,0,1,0,2,1,0},
                        {0,1,0,2,2,3,2,1},
                        {1,1,0,1,2,3,3,1},
                        {4,4,4,4,4,4,4,4}};
  
  
  /*
  for(int y=0; y<PLANET_HEIGHT; y++){
    for(int x=0; x<PLANET_WIDTH; x++){
      move(y, x+5);
      addch(palette[planet[y][x]]);
    }
  }
  while((PLANET_WIDTH+PLANET_HEIGHT)/2 <= x*x + y*y){
  	addch('/');
  	refresh();
  }
  /**/
  refresh();
}


