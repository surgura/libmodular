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
    @return             A pointer to the new node, or 0 if allocating memory was needed, but it failed.
**/
Mdr_LinkedListNode* Mdr_LinkedList_Append(Mdr_LinkedList* instance);

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
    @param  node        The node to get the next node from.
    @return             The next node, or 0 if the provided node was the last node.
**/
Mdr_LinkedListNode* Mdr_LinkedList_Next(Mdr_LinkedList* instance, Mdr_LinkedListNode* node);

/**
    Get the node before the given node.

    @param  instance    Pointer to the linked list instance.
    @param  node        The node to get the previous node from.
    @return             The previous node, or 0 if the provided node was the first node.
**/
Mdr_LinkedListNode* Mdr_LinkedList_Previous(Mdr_LinkedList* instance, Mdr_LinkedListNode* node);

/**
    Get the first node of the list.

    @param  instance    Pointer to the linked list instance.
    @return             The first node, or 0 if the list is empty.
**/
Mdr_LinkedListNode* Mdr_LinkedList_First(Mdr_LinkedList* instance);

/**
    Get the last node of the list.

    @param  instance    Pointer to the linked list instance.
    @return             The last node, or 0 if the list is empty.
**/
Mdr_LinkedListNode* Mdr_LinkedList_Last(Mdr_LinkedList* instance);

/**
    End header guard
**/
#endif // MDR_LINKED_LIST_FUNCTIONS_H
