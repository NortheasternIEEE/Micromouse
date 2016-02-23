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
    if (param[x][y].maped) {return;}
    direction options[4];
    visit(&param[x][y]);
    getSuccessors(param[x][y], options);
    for (int i = 0; i < 4; i++) {
        moveRobot(position, options[i]);
        map(position, param);
        // GO BACK
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