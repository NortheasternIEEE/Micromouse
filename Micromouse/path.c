//
//  path.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "path.h"


void findPath(node graph[mazeSize][mazeSize], location *start, location end[4], Link *bestPath,
              bWrap *finished) {
    // If you have already been to this node return  
    if (graph[start->x][start->y].maped == true) {
        return;
    }
    // If you are at the end generate the path
    if (((start->x == end[0].x) && (start->y == end[0].y)) ||
        ((start->x == end[1].x) && (start->y == end[1].y)) ||
        ((start->x == end[2].x) && (start->y == end[2].y)) ||
        ((start->x == end[3].x) && (start->y == end[3].y))) {
        dealWithPath(graph, start, bestPath);
        finished->value = true;
        return;
    }
    // Set the nodes maped value to true
    graph[start->x][start->y].maped = true;
    direction options[4];
    // Get where you can go from this node
    getSuccessors(graph[start->x][start->y], options);
    // Determine how you got to this node
    direction d = graph[start->x][start->y].parent;
    for (int i = 0; i < 4; i++) {
        if (options[i] != STOP && options[i] != d && !finished->value) {
            // Moves the location to the spot you are going to go
            updateLoc(start, options[i]);
            
            //printf("\nX = %d, Y = %d\n", start->x, start->y);
            //printD(reverse(options[i]));
            //printf("\n");
            
            // Set the parent of the node you are about to visit to the current node
            graph[start->x][start->y].parent = reverse(options[i]);
            
            findPath(graph, start, end, bestPath, finished);
            // Go back
            goBack(start, options[i]);
        }
    }
}



void dealWithPath(node graph[mazeSize][mazeSize], location *start, Link *best) {
    location temp;
    temp.x = start->x;
    temp.y = start->y;
    direction parent = graph[temp.x][temp.y].parent;
    add(best, parent);
    while (temp.x != 0 || temp.y != 0) {
        updateLoc(&temp, parent);
        parent = graph[temp.x][temp.y].parent;
        add(best, parent);
    }
    Link *conductor;
    conductor = malloc(sizeof(Link));
    conductor = best;
    while (conductor->next != NULL) {
        //printD(conductor->value);
        //printf("\n");
        conductor = conductor->next;
    }
}

void printD(direction d) {
    switch (d) {
        case RIGHT:
            printf("RIGHT");
            break;
        case LEFT:
            printf("LEFT");
            break;
        case UP:
            printf("UP");
            break;
        case DOWN:
            printf("DOWN");
            break;
        case STOP:
            printf("STOP");
            break;
        default:
            break;
    }
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
