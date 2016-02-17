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

void findPath(struct node graph[18][18], struct loc *start,
              struct loc end, Link *currPath, Link *bestPath);

void dealWithPath(Link *curr, Link *best);
void updateLoc(struct loc *pos, enum directions d);
void goBack(struct loc *pos, enum directions d);

#endif /* path_h */
