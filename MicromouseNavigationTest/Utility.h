#ifndef UTILITY_H_
#define UTILITY_H_

#include "Arduino.h"

#define signum(x) ((x >= 0) ? 1 : -1)

void configureTimer(Tcc*, IRQn_Type, uint16_t);
float floatMap(float, float, float, float, float);

/*
 * Used to define the size of the maze. Change this value and it will change the maze size for the entire 
 * project. Only define the mazeSize here and no where else.
 */
#define mazeSize 16

/*
 * An enumeration to represent one of the 4 directions that the micromouse can go.
 * To represent when the micromouse can not go a certain direction STOP is used.
 */
typedef enum directions {RIGHT, LEFT, UP, DOWN, STOP} direction;

/*
 * A struct that represents a node in the maze. For each square in the maze there will be a node so
 * for a maze of size 10 x 10 there will be 100 nodes in the maze. 
 * Within each node there are four booleans that represent if the micromouse is able to travel right,
 * left, up or down. The boolean mapped is used to determine if the mouse has already visited the cell
 * in the graph. The parent store the reverse of the direction the mouse had to move to get to this cell.
 * For example if the mouse starts at cell 0,0 and moves to cell 1,0, the mouse moves right, then 
 * the parent of cell 1,0 will be left.
 */
typedef struct node {
    bool right;
    bool left;
    bool up;
    bool down;
    bool mapped;
    int x;
    int y;
    direction parent;
} node;

/*
 * A struct that holds both x and y coordinates. Used to track the mouses' location during the program.
 */
typedef struct loc {
    int x;
    int y;
} location;

/*
 * Given the mouse is at location p, move the mouse in the direction specified by d and update its location
 */
void moveRobot(location *p, direction d);
/*
 * Set the specified location to the value specified by x and y
 */
void setLoc(location *spot, int x, int y);
/*
 * Given a node returns RIGHT if the mouse can move right and STOP if the mouse can not move RIGHT.
 */
direction goRight(node v);
/*
 * Given a node returns LEFT if the mouse can move right and STOP if the mouse can not move LEFT.
 */
direction goLeft(node v);
/*
 * Given a node returns UP if the mouse can move right and STOP if the mouse can not move UP.
 */
direction goUp(node v);
/*
 * Given a node returns DOWN if the mouse can move right and STOP if the mouse can not move DOWN.
 */
direction goDown(node v);
/*
 * Initialize the graph. Set every nodes' mapped value to false and parent to STOP
 */
void initializeGraph(node param[mazeSize][mazeSize]);
/*
 * Initialize the location to 0,0
 */
void initializeLoc(location *spot);
direction reverse(direction d);
void clearMapped(node param[mazeSize][mazeSize]);

#endif


