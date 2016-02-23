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

void findPath(node graph[mazeSize][mazeSize], location *start,
               location end, Link *currPath, Link *bestPath);

void dealWithPath(Link *curr, Link *best);
void updateLoc(location *pos, direction d);
void goBack(location *pos, direction d);

#endif /* path_h */
