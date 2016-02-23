//
//  path.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "path.h"


void findPath(node graph[mazeSize][mazeSize], location *start, location end, Link *currentPath, Link *bestPath) {
    if ((start->x == end.x) && (start->y == end.y)) {
        dealWithPath(currentPath, bestPath);
    }
    direction options[4];
    getSuccessors(graph[start->x][start->y], options);
    for (int i = 0; i < 4; i++) {
        updateLoc(start, options[i]);
        pushToEnd(currentPath, options[i]);
        findPath(graph, start, end, currentPath, bestPath);
        popFromEnd(currentPath);
        goBack(start, options[i]);
    }
}

void dealWithPath(Link *curr, Link *best) {
    // DO SOME SHIT
}

void updateLoc(location *p, direction d) {
    switch (d) {
        case RIGHT:
            p->x = p->x + 1;
            break;
        case LEFT:
            p->x = p->x - 1;
            break;
        case DOWN:
            p->y = p->y - 1;
            break;
        case UP:
            p->y = p->y + 1;
            break;
        case STOP:
            break;
        default:
            break;
    }
}

void goBack(location *p, direction d) {
    switch (d) {
        case RIGHT:
            updateLoc(p, LEFT);
            break;
        case LEFT:
            updateLoc(p, RIGHT);
            break;
        case UP:
            updateLoc(p, DOWN);
            break;
        case DOWN:
            updateLoc(p, UP);
            break;
        default:
            break;
    }
}