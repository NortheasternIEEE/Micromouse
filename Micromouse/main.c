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
    Link bestPath;
    enum directions ways[4];
    int size = NELEMS(graph);
    initializeGraph(graph);
    initializeLoc(&currentPoint);
    findPath(graph, &currentPoint, end, &bestPath);
    return 0;
}










