/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Include files
**/
#include "Modular/FactoryFunctions.h"
#include "LinkedListFunctions.h"
#include "Module.h"

void* GetCommonData(Mdr_Module* module)
{
    return (Mdr_U8*)module + sizeof(Mdr_Module);
}

void* GetInstanceData(Mdr_Module* module, void* instance)
{
    return (Mdr_U8*)instance + module->instanceOffset;
}

void Mdr_Initialize(Mdr_Factory* factory)
{
    factory->moduleInstancesSizeSum = 0;
    Mdr_LinkedList_Initialize(&factory->modules);
    Mdr_LinkedList_Initialize(&factory->instances);
}

void Mdr_Cleanup(Mdr_Factory* factory)
{
    Mdr_LinkedList_Cleanup(&factory->modules);
    Mdr_LinkedList_Cleanup(&factory->instances);
}

Mdr_Result Mdr_Register(Mdr_Factory* factory, Mdr_ModuleId* moduleResult, Mdr_U32 moduleSize, Mdr_U32 instanceSize,
                        void (*construct)(Mdr_ModuleId, Mdr_InstanceId), void (*destruct)(Mdr_ModuleId, Mdr_InstanceId))
{
    // Calculate size of the data in the linked list node
    Mdr_U32 nodeSize = sizeof(Mdr_Module) + moduleSize;

    // Add module to module list
    Mdr_LinkedListNode* moduleNode;
    if (Mdr_LinkedList_PushBack(&factory->modules, &moduleNode, nodeSize) == MDR_LINKEDLIST_ALLOC_ERROR)
        return MDR_ALLOC_ERROR; // Return with alloc error if an alloc error occurred in the linked list

    // Get module pointer
    void* moduleNodeData = Mdr_LinkedList_GetData(moduleNode);
    Mdr_Module* module = (Mdr_Module*)moduleNodeData;
    // Set module instance offset
    module->instanceOffset = factory->moduleInstancesSizeSum;
    // Set module construct and destruct functions
    module->construct = construct;
    module->destruct = destruct;

    // Increment module instance size sum with this modules instance size
    factory->moduleInstancesSizeSum += instanceSize;

    // Set result value
    *moduleResult = moduleNode;

    return MDR_SUCCESS;
}

void* Mdr_GetModuleCommonData(Mdr_ModuleId module)
{
    // Get pointer to the module
    void* moduleNodeData = Mdr_LinkedList_GetData(module);
    // Skip the module struct to go to the common data
    void* commonData = GetCommonData(moduleNodeData);

    return commonData;
}

Mdr_Result Mdr_Instantiate(Mdr_Factory* factory, Mdr_InstanceId* instanceResult)
{
    // Create new node in instance list
    Mdr_LinkedListNode* instanceNode;
    if (Mdr_LinkedList_PushBack(&factory->instances, &instanceNode, factory->moduleInstancesSizeSum) == MDR_LINKEDLIST_ALLOC_ERROR)
        return MDR_ALLOC_ERROR;

    // Iterate over all modules and call construct
    for (Mdr_LinkedListNode* moduleNode = factory->modules.first; moduleNode != 0; moduleNode = Mdr_LinkedList_Next(moduleNode))
    {
        Mdr_Module* module = Mdr_LinkedList_GetData(moduleNode);
        module->construct(moduleNode, instanceNode);
    }

    *instanceResult = instanceNode;

    return MDR_SUCCESS;
}

void Mdr_Destroy(Mdr_Factory* factory, Mdr_InstanceId instance)
{
    // Iterate over all modules reversely and call destruct
    for (Mdr_LinkedListNode* moduleNode = factory->modules.last; moduleNode != 0; moduleNode = Mdr_LinkedList_Previous(moduleNode))
    {
        Mdr_Module* module = Mdr_LinkedList_GetData(moduleNode);
        module->destruct(moduleNode, instance);
    }

    // Remove instance
    Mdr_LinkedList_Remove(&factory->instances, instance);
}

void* Mdr_GetModuleInstanceData(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    Mdr_Module* moduleData = Mdr_LinkedList_GetData(module);
    void* instanceData = Mdr_LinkedList_GetData(instance);
    return GetInstanceData(moduleData, instanceData);
}
