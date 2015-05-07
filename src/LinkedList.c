/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Include files
**/
#include "LinkedListFunctions.h"
#include <stdlib.h>

void Mdr_LinkedList_Initialize(Mdr_LinkedList* instance, u16 dataSize)
{
    instance->dataSize = dataSize;
    instance->firstNode = 0;
    instance->lastNode = 0;
}

void Mdr_LinkedList_Delete(Mdr_LinkedList* instance)
{

}

Mdr_LinkedList_Result Mdr_LinkedList_Append(Mdr_LinkedList* instance, Mdr_LinkedListNode** node)
{
    // Allocate memory for node.
    Mdr_LinkedListNode* newNode = malloc(instance->dataSize + 2 * sizeof(Mdr_LinkedListNode*));
    if(newNode == 0)
        return MDR_LINKEDLIST_ALLOC_FAIL;

    // Check if this is the first node
    if(instance->firstNode == 0)
    {
        // Set first node to new node
        instance->firstNode = newNode;

        // Set last node to new node
        instance->lastNode = newNode;

        // Skip to the previous node pointer;
        Mdr_LinkedListNode** previousNode = (u8*)newNode + instance->dataSize;

        // Set the previous node pointer to 0
        *previousNode = 0;

        // Skip to the next node pointer
        Mdr_LinkedListNode** nextNode = (u8*)previousNode + sizeof(Mdr_LinkedListNode*);

        // Set last node pointer to 0
        *nextNode = 0;
    }
    else
    {
        // Set last node next node to new node
        Mdr_LinkedListNode** lastNodeNextNode = (u8*)instance->lastNode + instance->dataSize + sizeof(Mdr_LinkedListNode*);
        *lastNodeNextNode = newNode;

        // Skip to the previous node pointer of new node;
        Mdr_LinkedListNode** previousNode = (u8*)newNode + instance->dataSize;

        // Set previous node pointer to last node
        *previousNode = instance->lastNode;

        // Skip to the next node pointer
        Mdr_LinkedListNode** nextNode = (u8*)previousNode + sizeof(Mdr_LinkedListNode*);

        // Set last node pointer to 0
        *nextNode = 0;

        // Set last node to new node
        instance->lastNode = newNode;
    }

    // Set return value
    *node = newNode;

    return MDR_LINKEDLIST_SUCCESS;
}

void Mdr_LinkedList_Remove(Mdr_LinkedList* instance, Mdr_LinkedListNode* node)
{

}

void* Mdr_LinkedList_GetData(Mdr_LinkedListNode* node)
{
    // The block of data is contained at the start of the node.
    return node;
}

Mdr_LinkedList_Result Mdr_LinkedList_Next(Mdr_LinkedList* instance, Mdr_LinkedListNode** nextNode, Mdr_LinkedListNode* node)
{
    Mdr_LinkedListNode** nodeNextNode = (u8*)node + instance->dataSize + sizeof(Mdr_LinkedListNode*);
    if(*nodeNextNode == 0)
    {
        return MDR_LINKEDLIST_NO_NODE;
    }
    else
    {
        *nextNode = *nodeNextNode;
    }
}

Mdr_LinkedList_Result Mdr_LinkedList_First(Mdr_LinkedList* instance, Mdr_LinkedListNode** firstNode)
{
    if(instance->firstNode == 0)
    {
        return MDR_LINKEDLIST_NO_NODE;
    }
    else
    {
        *firstNode = instance->firstNode;
        return MDR_LINKEDLIST_SUCCESS;
    }
}
