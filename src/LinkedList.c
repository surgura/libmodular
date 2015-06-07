/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Include files
**/
#include "Modular/LinkedListFunctions.h"
#include <stdlib.h>

void Mdr_LinkedList_Initialize(Mdr_LinkedList* list)
{
    list->first = 0;
    list->last = 0;
}

void Mdr_LinkedList_Cleanup(Mdr_LinkedList* list)
{
    Mdr_LinkedListNode* node = list->first;
    while(node != 0)
    {
        Mdr_LinkedListNode* toFree = node;
        node = node->next;
        free(toFree);
    }
}

Mdr_LinkedList_Result Mdr_LinkedList_PushBack(Mdr_LinkedList* list, Mdr_LinkedListNode** resultNode, u32 dataSize)
{
    // Calculate size of node
    u64 nodeSize = sizeof(Mdr_LinkedListNode) + dataSize;
    // Alocate memory for node
    Mdr_LinkedListNode* newNode = malloc(nodeSize);
    if(newNode == 0)
        return MDR_LINKEDLIST_ALLOC_ERROR;

    // If there is a last node
    if(list->last != 0)
    {
        // Set previous for new node to old last node
        newNode->previous = list->last;
        // Set new node next to 0
        newNode->next = 0;

        // Set next for old last
        list->last->next = newNode;
        // Set new node as last
        list->last = newNode;
    }
    else
    {
        // Set new node as last and first
        list->first = newNode;
        list->last = newNode;
        // Set previous and next of new node to 0
        newNode->next = 0;
        newNode->previous = 0;
    }

    // Set return value
    *resultNode = newNode;

    return MDR_LINKEDLIST_SUCCESS;
}

void Mdr_LinkedList_Remove(Mdr_LinkedList* list, Mdr_LinkedListNode* node)
{
    // If this is the first node
    if(node->previous == 0)
    {
        // Set first node to this nodes next node
        list->first = node->next;
    }
    else
    {
        // Set previous nodes next to this nodes next
        node->previous->next = node->next;
    }

    // If this is the last node
    if(node->next == 0)
    {
        // Set last node to this nodes previous node
        list->last = node->previous;
    }
    else
    {
        // Set next nodes previous to this nodes previous
        node->next->previous = node->previous;
    }

    // Free memory
    free(node);
}

Mdr_LinkedListNode* Mdr_LinkedList_Next(Mdr_LinkedListNode* node)
{
    return node->next;
}

Mdr_LinkedListNode* Mdr_LinkedList_Previous(Mdr_LinkedListNode* node)
{
    return node->previous;
}

void* Mdr_LinkedList_GetData(Mdr_LinkedListNode* node)
{
    // Skip node struct to get to the data
    return (u8*)node + sizeof(Mdr_LinkedListNode);
}
