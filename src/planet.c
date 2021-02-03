#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PLANET_WIDTH 8
#define PLANET_HEIGHT 5
#define PALETTE_SIZE 5
#define RADIUS 2.5

typedef struct {
    int palette_size;
    int height;
    int width;
    int* palette; // an array of pallete_size many ints that print as ncurses chars
    int* map; // an array of planet_height*planet_width ints representing indexes into the palette
    
} planet_t;

int init_planet(planet_t* planet, int palette_size, int width, int height){
    planet->palette_size = palette_size;
    planet->width = width;
    planet->height = height;
    planet->palette = malloc(sizeof(int) * palette_size);
    if(planet->palette == 0){
        return 0;
    }
    planet->map = malloc(sizeof(int) * height * width);
    if(planet->map == 0){
        free(planet->palette);
        return 0;
    }
    for(int i = 0; i < planet->palette_size; i++){
        planet->palette[i] = 0;
    }
    for(int i = 0; i < width*height; i++){
        planet->map[i] = 0;
    }
    return 1;
}

void destroy_planet(planet_t* planet){
    free(planet->palette);
    free(planet->map);
}

int in_elipse(
        double x, 
        double y, 
        double r, 
        double x_off, 
        double y_off, 
        double x_strech, 
        double y_strech){
    return r*r <= (y_strech*y-y_off)*(y_strech*y-y_off)+(x_strech*x-x_off)*(x_strech*x-x_off);
}

void main (void){
    planet_t planet;
    init_planet(&planet, PALETTE_SIZE, PLANET_WIDTH, PLANET_HEIGHT);
    
    memcpy(planet.palette,
        (int[]){'W', 'w', '.', '#', 'O'}, 
            sizeof(int)*planet.palette_size);
            
    memcpy(planet.map,
        (int[]){2, 3, 3, 3, 3, 3, 3, 2,
                2, 0, 0, 0, 0, 0, 0, 2,
                2, 0, 0, 0, 0, 0, 0, 2,
                2, 0, 0, 0, 0, 0, 0, 2,
                2, 3, 3, 3, 3, 3, 3, 2}, 
            sizeof(int)*planet.height*planet.width);
    
    //printf("%d %d %d %d %d\n", planet.palette[0], planet.palette[1], planet.palette[2], planet.palette[3], planet.palette[4]);

    initscr ();
    //start_color ();
    cbreak ();
    keypad (stdscr, TRUE);
    nodelay (stdscr, TRUE);
    noecho ();
    clear ();
    int hight, width;
    getmaxyx (stdscr, hight, width);
    
    int x, y;
    getyx (stdscr, y, x);
    
    move (2, 2);
    
    for (int y = 0; y < PLANET_HEIGHT; y++){
        for (int x = 0; x < PLANET_WIDTH; x++){
            move (y, x);
            if (in_elipse(x, y, 4, 0, 0, 1, 1)){
                addch ('/');
            }else{
                addch(planet.palette[planet.map[x+y*planet.width]]);
            }
        }
    }
    refresh();
}
