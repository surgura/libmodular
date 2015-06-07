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
#include "LinkedList.h"

/**
    Codes for the results of the linked list functions.
**/
typedef enum
{
    /**
        Everything went fine.
    **/
    MDR_LINKEDLIST_SUCCESS,
    /**
        Allocating memory was needed, but something went wrong.
    **/
    MDR_LINKEDLIST_ALLOC_ERROR
} Mdr_LinkedList_Result;

/**
    Initialize a linked list.

    @param  list    The list to initialize.
**/
void Mdr_LinkedList_Initialize(Mdr_LinkedList* list);

/**
    Cleanup a linked list. Frees all memory.
    After this, construct can be called again on the same list to use it again.

    @param  list    The list to clean up.
**/
void Mdr_LinkedList_Cleanup(Mdr_LinkedList* list);

/**
    Add a new node at the front of the list with the given size.

    @param  list        The list to add to.
    @param  resultNode  The variable to store the result pointer to the node in.
    @param  dataSize    The size of data to be contained in the node.
    @return MDR_SUCCESS     Everything went fine
            MDR_ALLOC_ERROR Allocating memory was needed, but something went wrong.
                            If this is returned, nothing is altered.
**/
Mdr_LinkedList_Result Mdr_LinkedList_PushBack(Mdr_LinkedList* list, Mdr_LinkedListNode** resultNode, u32 dataSize);

/**
    Remove a node from the list.

    @param  list        The list to remove from.
    @param  node        The node to remove.
**/
void Mdr_LinkedList_Remove(Mdr_LinkedList* list, Mdr_LinkedListNode* node);

/**
    Get the next node in the list.
    Returns NULL if this was the last node in the list.

    @param  node        The node to get the next sibling from.
    @return             The next node.
                        NULL if the provided node was the last one in the list.
**/
Mdr_LinkedListNode* Mdr_LinkedList_Next(Mdr_LinkedListNode* node);

/**
    Get the previous node in the list.
    Returns NULL if this was the first node in the list.

    @param  node        The node to get the previous sibling from.
    @return             The previous node.
                        NULL if the provided node was the first one in the list.
**/
Mdr_LinkedListNode* Mdr_LinkedList_Previous(Mdr_LinkedListNode* node);

/**
    Get the data from a node.

    @param  node        The node to get the data from.
**/
void* Mdr_LinkedList_GetData(Mdr_LinkedListNode* node);

/**
    End header guard
**/
#endif // MDR_LINKED_LIST_FUNCTIONS_H
