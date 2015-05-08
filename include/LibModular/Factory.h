/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Header guard
**/
#ifndef MDR_FACTORY_H
#define MDR_FACTORY_H

/**
    Include files
**/
#include "Types.h"
#include "LinkedList.h"

/**
    Result codes for LibModular functions.
**/
typedef enum
{
    /**
        The operation was successful.
    **/
    MDR_SUCCESS = 1,
    /**
        Allocating memory failed.
    **/
    MDR_ALLOC_FAIL = -1,
    /**
        No instance has yet been made.
    **/
    MDR_NO_INSTANCE = -2,
    /**
        There is at least one instance, so the requested action is not valid.
    **/
    MDR_HAS_INSTANCE = -3
} Mdr_Result;

/**
    Keeps all information about a LibModular instance.
    Do not alter the data contained.
**/
typedef struct
{
    /**
        All registered modules.
    **/
    Mdr_LinkedList modules;
    /**
        All created instances.
    **/
    Mdr_LinkedList instances;
    /**
        The amount of instances that are currently active.
    **/
    u32 instanceCount;
    /**
        The total sum of the size of a single instance of each module.
    **/
    u32 totalInstanceSize;
} Mdr_Factory;

/**
    Identifier for a registered module.
**/
typedef Mdr_LinkedListNode* ModuleID;
/**
    Identifier for an instance created via Instantiate.
**/
typedef Mdr_LinkedListNode* InstanceID;

/**
    Initializes a LibModular instance.

    @param  instance    The factory instance.
**/
void Mdr_ConstructFactory(Mdr_Factory* instance);

/**
    Destroys a LibModular instance.
    Cleans up all memory allocated by this library for the instance.
    Does not deallocate the instance itself, as it is user owned memory.
    the deleteInstance functions will be called.

    @param  instance    The factory instance.
**/
void Mdr_DestructFactory(Mdr_Factory* instance);

/**
    Register a module at the factory,
    which will be used when a modular instance is created.
    Can only be called when there are no instances.
    If an error is returned, all changes have already been reverted nicely.

    @param  instance        The factory instance.
    @param  newModuleId     Place to store the ID of the registered module, which can be used to request
                            the latest instance of the module.
    @param  userData        Pointer to user defined data that will be passed into the
                            instantiate function.
    @param  instanceSize    Size of an instance of the module.
    @param  instantiate     Function that will be called to create a module instance,
                            when a new modular instance is created.
                            The first argument is the pointer to the user data provided in this function.
                            The second argument is a block of memory for the new instance which needs to
                            be initialized.
    @param  deleteInstance  Function that will be called to delete a module instance.
                            The first argument is the pointer to the user data provided in this function.
                            The second argument is an initialized block of memory of the instance to delete.
    @return                 MDR_SUCCESS if everything went well.
                            MDR_ALLOC_FAIL if allocating memory was needed but it failed.
                            MDR_HAS_INSTANCE if there is at least one instance so calling this is not possible.
**/
Mdr_Result Mdr_RegisterModule(Mdr_Factory* instance, ModuleID* newModuleId,
    void* userData, const u16 instanceSize,
    void (*instantiate)(void*, void*),
    void (*deleteInstance)(void*, void*));

/**
    Remove a module from the factory.
    No instances may be there when this is done.

    @param  instance        The factory instance
    @param  moduleId        Id of the module to remove, obtained via the register function.
    @return                 MDR_SUCCESS if everything went well.
                            MDR_HAS_INSTANCE if ther eis at least one instance so calling this is not possible.
**/
Mdr_Result Mdr_UnregisterModule(Mdr_Factory* instance, ModuleID moduleId);

/**
    Get the latest created instance of a module with the given id.
    Make sure moduleId is valid, because this is not checked.
    If an error is returned, all changes have already been reverted nicely.

    @param  instance    The factory instance.
    @param  result      The place to store the pointer to the module instance.
    @param  moduleId    The id for the module received when registering the module.
    @return             MDR_SUCCESS when everything went well.
                        MDR_NO_INSTANCE when no instance has yet been made.
**/
Mdr_Result Mdr_GetLatestModuleInstance(Mdr_Factory* instance, void** result, const ModuleID moduleId);

/**
    Instantiate a modular instance through the factory,
    using all registered modules.
    The registered modules are instantiated and their initialize functions
    are called in the same order as they are registered.
    It is not valid to request modules instances of modules that have been
    registered after the one that is currently being handled,
    and this leads to undefined behaviour.
    If an error is returned, all changes have already been reverted nicely.

    @param  instance    The factory instance.
    @param  instanceId  Place to store the id of the new instance, which can be used
                        to delete the instance.
    @return             MDR_SUCCESS when everything went well.
                        MDR_ALLOC_FAIL if allocating memory was needed but it failed.
**/
Mdr_Result Mdr_Instantiate(Mdr_Factory* instance, InstanceID* instanceId);

/**
    Remove an instance instantiated earlier.
    Make sure instanceId is valid, because this is not checked.
    The deleteInstance function of each module is called with their instance
    as argument.

    @param  instance    The factory instance.
    @param  instanceId  The id of the instance.
    @return             MDR_SUCCESS when everything went well.
**/
Mdr_Result Mdr_DeleteInstance(Mdr_Factory* instance, InstanceID instanceId);

/**
    End header guard
**/
#endif // MDR_FACTORY_H
