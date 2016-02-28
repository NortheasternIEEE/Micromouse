//
//  path.h
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#ifndef path_h
#define path_h

#include <stdio.h>
#include "Utility.h"
#include "linkedlist.h"
#include "map.h"


typedef struct boolWrap {
    bool value;
}bWrap;

void findPath(node graph[mazeSize][mazeSize], location *start,
               location end, Link *bestPath, bWrap *finsihed);

void dealWithPath(node graph[mazeSize][mazeSize], location *start, Link *best);
void updateLoc(location *pos, direction d);
void goBack(location *pos, direction d);
/*
 * Print the given directions
 */
void printD(direction d);

#endif /* path_h */
