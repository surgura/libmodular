/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Header guard
**/
#ifndef MDR_FACTORY_FUNCTIONS_H
#define MDR_FACTORY_FUNCTIONS_H

/**
    Include files
**/
#include "Types.h"
#include "Factory.h"

/**
    Codes for the results of the factory functions.
**/
typedef enum
{
    /**
        Everything went fine.
    **/
    MDR_SUCCESS,
    /**
        Allocating memory was needed, but something went wrong.
    **/
    MDR_ALLOC_ERROR
} Mdr_Result;

// A certain modules part of an instance.
//Mdr_ModuleInstance
// Identifies a registered module
typedef Mdr_LinkedListNode* Mdr_ModuleId;
// Identifies an instance
typedef Mdr_LinkedListNode* Mdr_InstanceId;

/**
    Initialize a factory for use.

    @param  factory     The factory to initialize
**/
void Mdr_Initialize(Mdr_Factory* factory);

/**
    Clean up a factory and all its allocated memory.
    Invalidates everything.
    factory can be used again by calling initialize after this.

    Does not destroy instances in the usual way. destruct is not called.

    @param  factory     The factory to clean up.
**/
void Mdr_Cleanup(Mdr_Factory* factory);

/**
    Register a module at a factory.
    Creates space for a common object for all module instance.

    @param  factory         The factory to register at.
    @param  moduleResult    Location where the module identifier should be stored.
    @param  moduleSize      The size in bytes of the common object.
                            If this is zero, no space will be allocated,
                            and null pointers will be passed to functions with the common object as argument.
    @param  instanceSize    The size of an instance of the module.
                            If this is zero, no space will be allocated when a new instance is created,
                            and null pointers will be passed to function with the instance as argument.
    @param  construct       The function that is called when a new instance is instantiated.
                            void* arg0      A pointer to the common object
                            void* arg1      A pointer to the module instance object
    @param  destruct        The function that is called when an instance is destroyed.
                            void* arg0      A pointer to the common object
                            void* arg1      A pointer to the module instance object
    @return MDR_SUCCESS     Everything went fine.
            MDR_ALLOC_ERROR Allocating memory was needed, but it failed.
                            Nothing has been altered when this happens.
**/
Mdr_Result Mdr_Register(Mdr_Factory* factory, Mdr_ModuleId* moduleResult, u32 moduleSize, u32 instanceSize,
                        void (*construct)(Mdr_ModuleId, Mdr_InstanceId), void (*destruct)(Mdr_ModuleId, Mdr_InstanceId));

/**
    Get a pointer to the common data of the given module

    @param  module          The module to get the common data for.
**/
void* Mdr_GetModuleCommonData(Mdr_ModuleId module);

/**
    Create a new instance from all modules registered at the factory.
    For each registered module, it makes space for the modules instance,
    and calls the modules construct function.

    @param  factory         The factory at which the modules are registered.
**/
Mdr_Result Mdr_Instantiate(Mdr_Factory* factory, Mdr_InstanceId* instanceResult);

/**
    Destroy an instance.
    For each registered module, it calls the destruct function.
**/
void Mdr_Destroy(Mdr_Factory* factory, Mdr_InstanceId instance);

/**
    Get a pointer to the modules data part of an instance.
    @param  factory         The factory the module is registered at.
    @param  module          The module to get the instance data for.
    @param  instance        The instance to get the data from.
**/
void* Mdr_GetModuleInstanceData(Mdr_ModuleId module, Mdr_InstanceId instance);

/**
    End header guard
**/
#endif // MDR_FACTORY_FUNCTIONS_H
