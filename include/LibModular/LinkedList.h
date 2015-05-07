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

#include "Types.h"

/**
    A node in the list.
    It consists of 3 blocks.
    The first block contains space for the actual data.
    The second block is a pointer to the previous node.
    The third block is a pointer to the next node.
**/
typedef void Mdr_LinkedListNode;

/**
    A linked list with a data size defined on initialization.
**/
typedef struct
{
    /**
        Size of the data.
    **/
    u16 dataSize;
    /**
        The first node in the list.
    **/
    Mdr_LinkedListNode* firstNode;
    /**
        The last node in the list.
    **/
    Mdr_LinkedListNode* lastNode;
} Mdr_LinkedList;

/**
    End header guard
**/
#endif // MDR_LINKED_LIST_H
