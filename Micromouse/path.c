//
//  path.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "path.h"


void findPath(node graph[mazeSize][mazeSize], location *start, location end, Link *bestPath) {
    // If you have already been to this node return
    if (graph[start->x][start->y].maped == true) {
        return;
    }
    // If you are at the end generate the path
    if ((start->x == end.x) && (start->y == end.y)) {
        dealWithPath(graph, start, bestPath);
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
        if (options[i] != STOP && options[i] != d) {
            // Moves the location to the spot you are going to go
            updateLoc(start, options[i]);
            printf("\nX = %d, Y = %d\n", start->x, start->y);
            printD(reverse(options[i]));
            printf("\n");
            // Set the parent of the node you are about to visit to the current node
            graph[start->x][start->y].parent = reverse(options[i]);
            
            findPath(graph, start, end, bestPath);
            // Go back
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
    struct List path;
    ListInitialize(&path);
    location temp;
    temp.x = start->x;
    temp.y = start->y;
    direction parent = graph[temp.x][temp.y].parent;
    Link node;
    node.value = parent;
    pushToHead(&path, &node);
    while (temp.x != 0 || temp.y != 0) {
        updateLoc(&temp, parent);
        parent = graph[temp.x][temp.y].parent;
        Link n;
        n.value = parent;
        pushToHead(&path, &n);
    }
    ListHead(&path);
    while (path.current->next != NULL) {
        printf("FEE\n");
        ListNext(&path);
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