//
//  map.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "map.h"


void map(struct loc *position, struct node param[18][18]) {
    int x = position->x;
    int y = position->y;
    if (param[x][y].maped) {return;}
    enum directions options[4];
    visit(&param[x][y]);
    getSuccessors(param[x][y], options);
    for (int i = 0; i < 4; i++) {
        moveRobot(position, options[i]);
        map(position, param);
    }
}

void visit(struct node *n) {
    n->maped = true;
}

void getSuccessors(struct node v, enum directions array[4]) {
    array[0] = goRight(v);
    array[1] = goLeft(v);
    array[2] = goUp(v);
    array[3] = goDown(v);
}