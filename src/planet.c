#include <curses.h>
#include <stdio.h>
#define PLANET_WIDTH 12
#define PLANET_HEIGHT 11
#define PALETTE_SIZE 5
#define RADIUS 2.5
#define b 1
#define a 1


int
main (void) {
  initscr ();
  start_color ();
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
  int palette[PALETTE_SIZE] = {'x', 'x', 'x', 'x', 'x'};
  int planet[PLANET_HEIGHT][PLANET_WIDTH] = {{4,4,4,4,4,4,4,4},
                        {1,0,0,1,0,2,1,0},
                        {0,1,0,2,2,3,2,1},
                        {1,1,0,1,2,3,3,1},
                        {4,4,4,4,4,4,4,4}};
  
  for(int y=0; y<PLANET_HEIGHT; y++){
    for(int x=0; x<PLANET_WIDTH; x++){
      move(y, x);
      if(RADIUS*RADIUS <= (1*y-+5)*(2*y-+5)+(1*x-+8)*(1*x-+2)){
        addch('/');
      }else{
          addch(palette[planet[y][x]]);
    }
      //addch(palette[planet[y][x]]);
    }
  }
  /*
  while((PLANET_WIDTH+PLANET_HEIGHT)/2 <= x*x + y*y){
  	addch('/');
  	refresh();
  }
  /**/
  refresh();
}


