//lib imports
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//consant variables for planet
#define PLANET_WIDTH 9
#define PLANET_HEIGHT 7
#define PALETTE_SIZE 5
#define RADIUS 2.5

/*

*/

typedef struct { //the struct for the planet
    int palette_size; //size of the palette
    int height; //height of planet
    int width; //width of planet
    int* palette; //an array of pallete_size many ints that print as ncurses chars
    int* map; //an array of planet_height*planet_width ints representing indexes into the palette
    
} planet_t;

int init_planet(planet_t* planet, int palette_size, int width, int height){ //the function that gives info to a planet_t struct
    planet->palette_size = palette_size;
    planet->width = width;
    planet->height = height;
    planet->palette = malloc(sizeof(int) * palette_size); //allocates memory to the pallette
    if(planet->palette == 0){ //checks if the palette has the memory it needs, if it doesn't, it frees the memory that the palette is using and exits the function
        free(planet->palette);
        return 0;
    }
    planet->map = malloc(sizeof(int) * height * width);
    if(planet->map == 0){ ///checks if the map has the memory it needs, if it doesn't, it frees the memory that the map is using and exits the function
        free(planet->map);
        return 0;
    }
    for(int i = 0; i < planet->palette_size; i++){ //fills the palette with zeros to avoid any problems that may happen
        planet->palette[i] = 0;
    }
    for(int i = 0; i < width*height; i++){ //fills the map with zeros to avoid any problems that may happen
        planet->map[i] = 0;
    }
    return 1; //exits the function as the planet struct is now ready to use
}

void destroy_planet(planet_t* planet){ //a function to free the memory from the planet and basically 'destroy' it
    free(planet->palette);
    free(planet->map);
}

int in_elipse( //a function to calculate whether the cursor is inside of the eclipse
        double x, //cursor x
        double y, //cursor y
        double r, //planet radius
        double x_off, //offset of x to move the planet
        double y_off, //offset of y to move the planet
        double x_strech, //how much you want to strech the x axis
        double y_strech){ //how much you want to strech the y axis
    return r*r <= (x_strech*x-x_off)*(x_strech*x-x_off)+(y_strech*y-y_off)*(y_strech*y-y_off); //returns the equation to check if the cursor is in the eclipse
}

void main (void){ //start of main function
    planet_t planet;
    init_planet(&planet, PALETTE_SIZE, PLANET_WIDTH, PLANET_HEIGHT);
    
    memcpy(planet.palette,
        (int[]){' ' | COLOR_PAIR(4), ' ' | COLOR_PAIR(2), ' ' | COLOR_PAIR(1), ' ' | COLOR_PAIR(2), ' ' | COLOR_PAIR(5)}, 
            sizeof(int)*planet.palette_size); //copying the wanted contents into the array
            
    memcpy(planet.map,
        (int[]){1, 1, 1, 1, 0, 0, 0, 0, 1,
                1, 1, 0, 0, 0, 0, 1, 0, 0,
                0, 0, 0, 1, 0, 0, 1, 1, 0,
                0, 0, 1, 1, 1, 0, 1, 1, 0,
                1, 0, 0, 1, 1, 0, 1, 0, 0,
                1, 1, 0, 0, 1, 0, 0, 0, 1,
                1, 1, 1, 0, 0, 0, 1, 1, 1}, 
            sizeof(int)*planet.height*planet.width); //copying the wanted contents into the array
    
    //printf("%d %d %d %d %d\n", planet.palette[0], planet.palette[1], planet.palette[2], planet.palette[3], planet.palette[4]);

    initscr ();
    if(!has_colors()){ //checks if the terminal supports color and if it doesn't, the program exits
        endwin(); //closes the window
        printf("Your terminal doesn't support color"); //notifies the user that their terminal does not support color
        exit(1); //exits the program
    }
    start_color (); //starts color as we know the terminal does not support color
    //implementing color pairs
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    //done implementing color pairs, now setting up the window
    cbreak (); //makes it so the terminal prints one character at a time
    keypad (stdscr, TRUE); //enables input from special characters
    nodelay (stdscr, TRUE); //enables no delay
    noecho (); //disbales echoing of typed characters
    clear (); //clears the window
    int hight, width; //width and height of the window
    getmaxyx (stdscr, hight, width);//gets the values for the width and height of  the window
    
    int x, y; //x and y of cursor
    getyx (stdscr, y, x); //gets x and y of cursor
    
    move (2, 2); //moves to 2,2 to print better
    int offset = 0; //offset of printing, used to make the planet spin
    while(1){ //while loop to make planet spin forever
        for (int y = 0; y < PLANET_HEIGHT; y++){ 
            for (int x = 0; x < PLANET_WIDTH; x++){ //2 layered for loop to draw the planet
                move (y, x); //moves to the wanted x and y locations
                if (in_elipse(x, y, 2.2, 2.5, 3, 0.6, 1)){ //checks if the cursor is in the eclipse
                    addch (' ' | COLOR_PAIR(7)); //makes the mask
                }else{
                    addch(planet.palette[planet.map[(x+offset)%planet.width+y*planet.width]]); //prints the map of the planet inside the mask
                }
            }
        }
        refresh(); //refreshes the screen
        sleep(1); //waits about a second before anymore actions
        offset += 1; //increments the offset
    }
    endwin(); //closes the window
}
