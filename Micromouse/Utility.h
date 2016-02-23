//
//  Utility.h
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#ifndef Utility_h
#define Utility_h

#include <stdio.h>
#include <stdbool.h>
#define mazeSize 16


typedef enum directions {RIGHT, LEFT, UP, DOWN, STOP} direction;

typedef struct node {
    bool right;
    bool left;
    bool up;
    bool down;
    bool maped;
    direction parent;
} node;

typedef struct loc {
    int x;
    int y;
} location;


void moveRobot(location *p, direction d);
void setLoc(location *spot, int x, int y);
direction goRight(node v);
direction goLeft(node v);
direction goUp(node v);
direction goDown(node v);
void initializeGraph(node param[mazeSize][mazeSize], int size);
void initializeLoc(location *spot);


#endif /* Utility_h */
