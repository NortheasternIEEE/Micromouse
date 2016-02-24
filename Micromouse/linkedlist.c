//
//  linkedlist.c
//  Micromouse
//
//  Created by Matthew Murphy on 2/16/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "linkedlist.h"

void ListInitialize (struct List *list)
{
	list->head = NULL;
	list->current = NULL;
	list->previous = NULL;
}

//Move to next location on lilst
void ListNext(struct List *list)
{
	//if there is a next position on the list
	if (list->current)
	{
		//set the previous pointer to current and the current pointer
		//ti the next pointer
		list->previous = list->current;
		list->current = list->current->next;
	}
}

//move position to head
void ListHead(struct List *list)
{
	//set the previous position to NULL
	list->previous = NULL;
	//set current position to head
	list->current = list->head;
}

// insert new node into list
void ListInsert(struct List *list, Link *lNode1)
{
	//intialize next pointer in car to point to current position in list
	lNode1->next = list->current;
	//if list is currently at head, then set the head to new node
	if(list->current == list->head)
	{
		list->head = lNode1;
	}
	// else set the previous node struct's next to point to the new node
	else
	{
		list->previous->next = lNode1;
	}
	//set list to be at current car
	list->current = lNode1;
}	

// remove car from ist
void ListRemove(struct List*list)
{
	//remove element if current element at head of list
	if(list->current == list->head)
	{
		list->head = list->current->next;
	}
	else
	{	//set previous car to point to next one, skipping over
		//removed car
		list->previous->next = list->current->next;
	}
	Link *next = list->current->next;
	free(list->current);
	list->current = next;
}
// assumes Link pointer declared in main
void pushToHead(struct List *list, Link *lNode1)
{
	ListHead(list);
	ListInsert(&list, lNode1);
}

void popFromEnd(struct List *list)
{
	while (list->current->next != NULL)
	{
		ListNext(list);
	}
	ListRemove(list);	
}

void pushToEnd(struct List *list, Link *lNode1)
{
	while (list->current->next != NULL)
	{
		ListNext(list);
	}
	ListInsert(list, lNode1);
}
