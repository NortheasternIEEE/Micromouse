//
//  path.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "path.h"


void findPath(node graph[mazeSize][mazeSize], location *start, location end, Link *bestPath) {
    if (graph[start->x][start->y].maped == true) {
        return;
    }
    if ((start->x == end.x) && (start->y == end.y)) {
        dealWithPath(graph, start, bestPath);
        return;
    }
    graph[start->x][start->y].maped = true;
    printf("Location: x = %d ", start->x);
    printf("y = %d\n", start->y);
    direction options[4];
    getSuccessors(graph[start->x][start->y], options);
    direction d = graph[start->x][start->y].parent;
    d = reverse(d);
    for (int i = 0; i < 4; i++) {
        if (options[i] != STOP && options[i] != d) {
            updateLoc(start, options[i]);
            graph[start->x][start->y].parent = options[i];
            //pushToEnd(currentPath, options[i]);
            findPath(graph, start, end, bestPath);
            //popFromEnd(currentPath);
            goBack(start, options[i]);
        }
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

void dealWithPath(node graph[mazeSize][mazeSize], location *start, Link *best) {
    // DO SOME SHIT
    printf("Made it to the end");
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
    
    printf("Go Back: x = %d ", p->x);
    printf("y = %d\n", p->y);
}