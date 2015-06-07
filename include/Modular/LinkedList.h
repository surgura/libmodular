/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Header guard
**/
#ifndef MDR_LINKED_LIST_H
#define MDR_LINKED_LIST_H

/**
    Include files
**/
#include "Types.h"

/**
    A node in the linked list.
**/
typedef struct Mdr_LinkedListNode
{
    struct Mdr_LinkedListNode* previous;
    struct Mdr_LinkedListNode* next;
} Mdr_LinkedListNode;

/**
    A doubly linked list with arbitrary size for each node.
**/
typedef struct
{
    Mdr_LinkedListNode* first;
    Mdr_LinkedListNode* last;
} Mdr_LinkedList;

/**
    End header guard
**/
#endif // MDR_LINKED_LIST_H
