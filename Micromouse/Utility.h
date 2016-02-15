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


struct node {
    bool right;
    bool left;
    bool up;
    bool down;
    bool maped;
};

struct loc {
    int x;
    int y;
};

enum directions {RIGHT, LEFT, UP, DOWN, STOP};


void moveRobot(struct loc *p, enum directions d);
void setLoc(struct loc *spot, int x, int y);
enum directions goRight(struct node v);
enum directions goLeft(struct node v);
enum directions goUp(struct node v);
enum directions goDown(struct node v);
void initializeGraph(struct node param[18][18], int size);
void initializeLoc(struct loc *spot);


#endif /* Utility_h */
