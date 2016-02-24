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
} Link;

struct List
{
	struct lNode *head;
	struct lNode *current;
	struct lNode *previous;
}

void pushToEnd(struct List *list, Link *lNode1);
void pushToHead(struct List *list, Link *lNode1);
void popFromEnd(struct List *list);
void ListInitialize(struct List *list);
void ListNext(struct List *list);
void ListHead(struct List *list);
void ListInsert(struct List *list, Link *lNode1);
void ListRemove(struct List *list);

#endif /* linkedlist_h */
