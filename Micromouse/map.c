//
//  map.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "map.h"


void map(location *position, node param[mazeSize][mazeSize]) {
    int x = position->x;
    int y = position->y;
    // If you have already been to this node return
    if (param[x][y].maped) {return;}
    printf("X = %d, Y = %d\n",x, y);
    direction options[4];
    // Visit the node to get all the relevant information you need
    visit(&param[x][y]);
    // Get all the possible ways the mouse can move from this cell
    getSuccessors(param[x][y], options);
    for (int i = 0; i < 4; i++) {
        // Move the mouse that direction and update its location
        moveRobot(position, options[i]);
        printf("Moved to: ");
        printf("X = %d, Y = %d\n",position->x, position->y);
        // Map the maze starting from that new location
        map(position, param);
        // GO BACK - Not implemented yet
        moveRobot(position, reverse(options[i]));
    }
}

void visit(node *n) {
    n->maped = true;
}

void getSuccessors(node v, direction array[4]) {
    array[0] = goRight(v);
    array[1] = goLeft(v);
    array[2] = goUp(v);
    array[3] = goDown(v);
}