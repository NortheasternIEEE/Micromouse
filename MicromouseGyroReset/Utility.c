//
//  Utility.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "Utility.h"


void moveRobot(location *p, direction d) {
    switch (d) {
        case RIGHT:
            // MOVE THE MOUSE RIGHT
            // UPDATE ITS POSITION
            p->x = p->x + 1;
            break;
        case LEFT:
            // MOVE THE MOUSE LEFT
            // UPDATE ITS POSITION
            p->x = p->x - 1;
            break;
        case DOWN:
            // MOVE THE MOUSE DOWN
            // UPDATE ITS POSITION
            p->y = p->y - 1;
            break;
        case UP:
            // MOVE THE MOUSE UP
            // UPDATE ITS POSITION
            p->y = p->y + 1;
            break;
        case STOP:
            // DO NOTHING
            break;
        default:
            break;
    }
}

void initializeLoc(location *spot) {
    spot->x = 0;
    spot->y = 0;
}

void  setLoc(location *spot, int x, int y) {
    spot->x = x;
    spot->y = y;
}

void initializeGraph(node param[mazeSize][mazeSize]) {
    for (int i = 0; i < mazeSize; i ++) {
        for (int j = 0; j < mazeSize; j++) {
            if (i == 0) {
                // IF i == 0 then you are on the left edge of the maze so the mouse can not move left
                param[i][j].left = false;
            } else {
                param[i][j].left = true;
            }
            if (i == mazeSize - 1){
                // if i == mazeSize - 1 you are on the right edge so the mouse can not move right
                param[i][j].right = false;
            } else {
                param[i][j].right = true;
            }
            if (j == 0) {
                // If j == 0 then you are on the bottom edge so the mouse can not move down
                param[i][j].down = false;
            } else {
                param[i][j].down = true;
            }
            if (j == mazeSize -1) {
                // if j == mazeSize - 1 then you are on the top edge so the mouse can not move up
                param[i][j].up = false;
            } else {
                param[i][j].up = true;
            }
            param[i][j].mapped = false;
            param[i][j].parent = STOP;
        }
    }
}

direction goRight(node v) {
    if (v.right) {
        return RIGHT;
    } else {
        return STOP;
    }
}
direction goLeft(node v) {
    if (v.left) {
        return LEFT;
    } else {
        return STOP;
    }
}
direction goUp(node v) {
    if (v.up) {
        return UP;
    } else {
        return STOP;
    }
}
direction goDown(node v) {
    if (v.down) {
        return DOWN;
    } else {
        return STOP;
    }
}

direction reverse(direction d) {
    switch (d) {
        case RIGHT:
            return LEFT;
            break;
        case LEFT:
            return RIGHT;
            break;
        case DOWN:
            return UP;
            break;
        case UP:
            return DOWN;
            break;
        case STOP:
            return STOP;
            break;
        default:
            return STOP;
            break;
    }
}

void clearMapped(node param[mazeSize][mazeSize]) {
    for (int i = 0; i < mazeSize; i ++) {
        for (int j = 0; j < mazeSize; j++) {
            param[i][j].mapped = false;
        }
    }
}


