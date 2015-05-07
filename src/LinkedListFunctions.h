/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Header guard
**/
#ifndef MDR_LINKED_LIST_FUNCTIONS_H
#define MDR_LINKED_LIST_FUNCTIONS_H

/**
    Include files
**/
#include "LibModular/LinkedList.h"

/**
    Result from a linked list function call that can have an error.
**/
typedef enum
{
    /**
        Everything went fine.
    **/
    MDR_LINKEDLIST_SUCCESS = 1,
    /**
        Allocating memory was needed, but it failed.
    **/
    MDR_LINKEDLIST_ALLOC_FAIL = -1,
    /**
        There is no node anymore when calling next, previous, first, or last.
    **/
    MDR_LINKEDLIST_NO_NODE = -2
} Mdr_LinkedList_Result;

/**
    Initialize a linked list.

    @param  instance    Pointer to the linked list instance.
    @param  dataSize    Size of the data contained in a linked list node.
**/
void Mdr_LinkedList_Initialize(Mdr_LinkedList* instance, u16 dataSize);

/**
    Cleanup a linked list and free all allocated memory.

    @param  instance    Pointer to the linked list instance.
**/
void Mdr_LinkedList_Delete(Mdr_LinkedList* instance);

/**
    Create a new node at the end of the list.

    @param  instance    Pointer to the linked list instance.
    @param  node        Location to store the node at, so it can be used in other functions.
    @return             MDR_LINKEDLIST_SUCCESS if everything went fine.
                        MDR_LINKEDLIST_ALLOC_FAIL if allocating memory was needed, but it failed.
**/
Mdr_LinkedList_Result Mdr_LinkedList_Append(Mdr_LinkedList* instance, Mdr_LinkedListNode** node);

/**
    Remove a node from the list.

    @param  instance    Pointer to the linked list instance.
    @param  node        The node to remove.
**/
void Mdr_LinkedList_Remove(Mdr_LinkedList* instance, Mdr_LinkedListNode* node);

/**
    Get a pointer to the data stored in a node.

    @param  node    The node to get the data from.
    @return         A pointer to the data.
**/
void* Mdr_LinkedList_GetData(Mdr_LinkedListNode* node);

/**
    Get the node after the given node.

    @param  instance    Pointer to the linked list instance.
    @param  nextNode    The place to store the next node at.
    @param  node        The node to get the next node from.
    @return             MDR_LINKEDLIST_SUCCESS if everything went fine.
                        MDR_LINKEDLIST_NO_NODE if node is the last node in the list.
**/
Mdr_LinkedList_Result Mdr_LinkedList_Next(Mdr_LinkedList* instance, Mdr_LinkedListNode** nextNode, Mdr_LinkedListNode* node);

/**
    Get the first node of the list.

    @param  instance    Pointer to the linked list instance.
    @param  firstNode   Place to store the result node at.
    @return             MDR_LINKEDLIST_SUCCESS if everything went fine.
                        MDR_LINKEDLIST_NO_NODE if the list is empty.
**/
Mdr_LinkedList_Result Mdr_LinkedList_First(Mdr_LinkedList* instance, Mdr_LinkedListNode** firstNode);

/**
    End header guard
**/
#endif // MDR_LINKED_LIST_FUNCTIONS_H
