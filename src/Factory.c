/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Include files
**/
#include "LibModular/Factory.h"
#include "LinkedListFunctions.h"

typedef struct
{
    void* userData;
    u16 instanceSize;
    void (*instantiate)(void*, void*);
    void (*deleteInstance)(void*, void*);
} Mdr_Module;

void Mdr_ConstructFactory(Mdr_Factory* instance)
{
    Mdr_LinkedList_Initialize(&instance->modules, sizeof(Mdr_Module));
    instance->instanceCount = 0;
    instance->totalInstanceSize = 0;
}

void Mdr_DestructFactory(Mdr_Factory* factory)
{
    // If there are no instances, there is no need to delete all instances,
    // and no need to destruct the instance list, because it has never been constructed.
    if(!factory->instanceCount == 0)
    {
        // Get pointer to first instance data.
        // If 0 is returned, we set instanceNode to 0 so we know there is no data.
        Mdr_LinkedListNode* instanceNode;
        if(Mdr_LinkedList_Last(&factory->instances, &instanceNode) < 0)
        {
            instanceNode = 0;
        }
        // Iterate over all instances
        for(u32 i = 0; i < factory->instanceCount; ++i)
        {
            // Get instance data as byte pointer
            u8* instances = Mdr_LinkedList_GetData(instanceNode);

            // Get a pointer to the first node of the modules
            // Only do something if there are actually modules registered.
            Mdr_LinkedListNode* moduleNode;
            if(Mdr_LinkedList_Last(&factory->modules, &moduleNode) > 0)
            {
                // Iterate over all modules
                do
                {
                    // Get module data
                    Mdr_Module* module = Mdr_LinkedList_GetData(moduleNode);
                    // Call delete for module
                    module->deleteInstance(module->userData, instances);
                    // Go to next module instance memory location
                    instances += module->instanceSize;
                } while(Mdr_LinkedList_Previous(&factory->modules, &moduleNode, moduleNode) > 0);
            }

            // Go to next instance if there is any data
            if(instanceNode != 0)
            {
                Mdr_LinkedList_Previous(&factory->instances, &instanceNode, instanceNode);
            }
        }

        // Destruct instance list
        Mdr_LinkedList_Delete(&factory->instances);
    }

    // Destruct module list
    Mdr_LinkedList_Delete(&factory->modules);
}

Mdr_Result Mdr_RegisterModule(Mdr_Factory* instance, ModuleID** newModuleId, void* userData,
    const u16 instanceSize, void (*instantiate)(void*, void*), void (*deleteInstance)(void*, void*))
{
    // Check if there there is one or more instances
    if(instance->instanceCount > 0)
    {
        // We cannot have instances when we add modules.
        return MDR_HAS_INSTANCE;
    }

    // Add a new node to the modules linked list
    Mdr_LinkedListNode* node;
    if(Mdr_LinkedList_Append(&instance->modules, &node) < 0)
    {
        // Appending has failed, the only option being allocation fail.
        return MDR_ALLOC_FAIL;
    }

    // Initialize module
    Mdr_Module* module = Mdr_LinkedList_GetData(node);
    module->userData = userData;
    module->instanceSize = instanceSize;
    module->instantiate = instantiate;
    module->deleteInstance = deleteInstance;

    // Increment size of the big instance.
    instance->totalInstanceSize += instanceSize;
}

Mdr_Result Mdr_GetLatestModuleInstance(Mdr_Factory* instance, void** result, const ModuleID* moduleId)
{
    // TODO
}

Mdr_Result Mdr_Instantiate(Mdr_Factory* instance, InstanceID** instanceId)
{
    // If there are no instances yet, we first have to initialize the instance list
    if(instance->instanceCount == 0)
    {
        Mdr_LinkedList_Initialize(&instance->instances, instance->totalInstanceSize);
    }

    // Pointer to the instance data as byte pointer
    u8* instances;

    // If total instance size is 0, we can skip appending a new instance.
    if(instance->totalInstanceSize > 0)
    {
        // Append a new instance to the list
        Mdr_LinkedListNode* instancesNode;
        if(!Mdr_LinkedList_Append(&instance->instances, &instancesNode))
        {
            // Appending has failed, the only option being allocation fail.
            return MDR_ALLOC_FAIL;
        }

        instances = Mdr_LinkedList_GetData(instancesNode);

        // Set instanceId return value
        *instanceId = instancesNode;
    }
    else
    {
        // If total instance size is 0, we don't have data.
        // instanceId does also not matter then, as the only thing it is used for,
        // is finding the data which matches this instance. As data for all instances
        // is 0, this is equal for every instance.
        instances = 0;
    }

    // Get a pointer to the first node of the modules
    // Only initialize if there are actually module instances to initialize.
    Mdr_LinkedListNode* moduleNode;
    if(Mdr_LinkedList_First(&instance->modules, &moduleNode) > 0)
    {
        // Iterate over all modules
        do
        {
            // Get module data
            Mdr_Module* module = Mdr_LinkedList_GetData(moduleNode);
            // Call module instantiate of module instance memory location
            module->instantiate(module->userData, instances);
            // Go to next module instance memory location
            instances += module->instanceSize;
        } while(Mdr_LinkedList_Next(&instance->modules, &moduleNode, moduleNode) > 0);
    }

    // Increment instance count
    ++instance->instanceCount;

    return MDR_SUCCESS;
}

Mdr_Result Mdr_DeleteInstance(Mdr_Factory* instance, InstanceID* instanceId)
{
    // TODO also make sure you check if the totalInstanceSize is 0
}
