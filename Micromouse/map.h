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

/*
 * Updates an array of length 4 with the four possible ways the mouse can travel.
 * The first directions are stored in the array as RIGHT, LEFT, UP and then DOWN
 * If the mouse can move RIGHT, LEFT, UP or DOWN the corresponding value is stored in the array
 * otherwise STOP is stored
 */
void getSuccessors(node v, direction array[4]);
/*
 * Maps the maze from the starting positon
 */
void map(location *position, node param[mazeSize][mazeSize]);
/*
 * When a mouse first enters a unseen node preforms all the necessary actions 
 */
void visit(node *n);

void getSuccessors1(node param[mazeSize][mazeSize], node v, direction array[4], int x, int y);

bool canMove(location *p, direction d, node param[mazeSize][mazeSize]);

#endif /* map_h */
