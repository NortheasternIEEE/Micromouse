//
//  main.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/9/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include "Utility.h"
#include "map.h"
#include "path.h"

#define NELEMS(x) (sizeof(x)/sizeof(x[0]))



int main(int argc, const char * argv[]) {
    struct node graph[mazeSize][mazeSize];
    struct loc currentPoint;
    location end;
    end.x = 8;
    end.y = 8;
    Link *bestPath;
    bestPath = malloc(sizeof(Link));
    bestPath->value = STOP;
    bestPath->next = NULL;
    enum directions ways[4];
    int size = NELEMS(graph);
    bWrap finished;
    finished.value = false;
    initializeGraph(graph);
    initializeLoc(&currentPoint);
    map(&currentPoint, graph);
    findPath(graph, &currentPoint, end, bestPath, &finished);
    Link *conductor;
    conductor = malloc(sizeof(Link));
    conductor = bestPath;
    while (conductor->next != NULL) {
        printD(conductor->value);
        printf("\n");
        conductor = conductor->next;
    }
    return 0;
}










