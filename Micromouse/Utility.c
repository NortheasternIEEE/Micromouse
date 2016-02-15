//
//  Utility.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "Utility.h"


void moveRobot(struct loc *p, enum directions d) {
    switch (d) {
        case RIGHT:
            // MOVE RIGHT
            p->x = p->x + 1;
            break;
        case LEFT:
            // MOVE LEFT
            p->x = p->x - 1;
            break;
        case DOWN:
            // MOVE DOWN
            p->y = p->y - 1;
            break;
        case UP:
            // MOVE UP
            p->y = p->y + 1;
            break;
        case STOP:
            // DO NOTHING
            break;
        default:
            break;
    }
}

void initializeLoc(struct loc *spot) {
    spot->x = 0;
    spot->y = 0;
}

void  setLoc(struct loc *spot, int x, int y) {
    spot->x = x;
    spot->y = y;
}

void initializeGraph(struct node param[18][18], int size) {
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size; j++) {
            if (i == 0) {
                param[i][j].down = false;
            } else {
                param[i][j].down = true;
            }
            if (i == size - 1){
                param[i][j].up = false;
            } else {
                param[i][j].up = true;
            }
            if (j == 0) {
                param[i][j].left = false;
            } else {
                param[i][j].left = true;
            }
            if (j == size -1) {
                param[i][j].right = false;
            } else {
                param[i][j].right = true;
            }
            param[i][j].maped = false;
        }
    }
}

enum directions goRight(struct node v) {
    if (v.right) {
        return RIGHT;
    } else {
        return STOP;
    }
}
enum directions goLeft(struct node v) {
    if (v.left) {
        return LEFT;
    } else {
        return STOP;
    }
}
enum directions goUp(struct node v) {
    if (v.up) {
        return UP;
    } else {
        return STOP;
    }
}
enum directions goDown(struct node v) {
    if (v.down) {
        return DOWN;
    } else {
        return STOP;
    }
}

