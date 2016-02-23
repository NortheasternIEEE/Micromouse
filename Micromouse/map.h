//
//  map.h
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#ifndef map_h
#define map_h

#include <stdio.h>
#include "Utility.h"


void getSuccessors(node v, direction array[4]);
void map(location *position, node param[mazeSize][mazeSize]);
void visit(node *n);

#endif /* map_h */
