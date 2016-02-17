//
//  linkedlist.h
//  Micromouse
//
//  Created by Matthew Murphy on 2/16/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#ifndef linkedlist_h
#define linkedlist_h

#include <stdio.h>
#include "Utility.h"

typedef struct lNode {
    enum directions value;
    struct lNode *next;
    struct lNode *prev;
} Link;

void pushToEnd(Link *head, enum directions value);
void pushToHead(Link **head, enum directions value);

#endif /* linkedlist_h */
