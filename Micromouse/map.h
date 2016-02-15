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


void getSuccessors(struct node v, enum directions array[4]);
void map(struct loc *position, struct node param[18][18]);
void visit(struct node *n);

#endif /* map_h */
