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
        Everything went as expected.
    **/
    MDR_SUCCESS,
    /**
        Allocing memory was needed but it failed.
        No data was changed.
    **/
    MDR_ALLOC_ERROR
} Mdr_Result;

/**
    An identifier of a module registered at a factory.
**/
typedef Mdr_LinkedListNode* Mdr_ModuleId;

/**
    An identifier of an instance created with a factory.
**/
typedef Mdr_LinkedListNode* Mdr_InstanceId;

/**
    Initialize a factory.

    @param  factory         The factory structure to initialize at
**/
void Mdr_Initialize(Mdr_Factory* factory);

/**
    Clean up a factory and all its allocated memory.
    Invalidates everything.
    Factory structure is free to use as if it where never used.

    Does not destroy instances in the usual way. destruct is not called.

    @param  factory         The factory to clean up.
**/
void Mdr_Cleanup(Mdr_Factory* factory);

/**
    Register a module at a factory.
    Creates space for a common object for all module instances.

    @param  factory         The factory to register at.
    @param  moduleResult    Location where the module identifier should be stored.
    @param  moduleSize      The size in bytes of the common object.
                            If this is zero, no space will be allocated,
                            and Mdr_GetModuleCommonData will return a null pointer.
    @param  instanceSize    The size of an instance of the module.
                            If this is zero, no space will be allocated when a new instance is created,
                            and Mdr_GetModuleInstanceData will return a null pointer.
    @param  construct       The function that is called when a new instance is instantiated.
                            arg0    The id of this module.
                            arg1    The id of the instance being created.
    @param  destruct        The function that is called when an instance is destroyed.
                            arg0    The id of this module.
                            arg1    The id of the instance being destroyed.
    @return                 How executing the function went.
            MDR_SUCCESS     Everything went as expected.
            MDR_ALLOC_ERROR Allocing memory was needed but it failed.
                            No data was changed.
**/
Mdr_Result Mdr_Register(Mdr_Factory* factory, Mdr_ModuleId* moduleResult, Mdr_U32 moduleSize, Mdr_U32 instanceSize,
                        void (*construct)(Mdr_ModuleId, Mdr_InstanceId), void (*destruct)(Mdr_ModuleId, Mdr_InstanceId));

/**
    Get a pointer to the common data of the given module

    @param  module          The module to get the common data for.
    @return                 A pointer to the common data.
**/
void* Mdr_GetModuleCommonData(Mdr_ModuleId module);

/**
    Create a new instance from all modules registered at the factory.
    For each registered module, it makes space for the modules instance,
    and calls the modules construct function.

    @param  factory         The factory at which the modules are registered.
    @param  instanceResult  A variable in which the unique id for the instance will be stored.
    @return                 How executing the function went.
            MDR_SUCCESS     Everything went as expected.
            MDR_ALLOC_ERROR Allocing memory was needed but it failed.
                            No data was changed.
**/
Mdr_Result Mdr_Instantiate(Mdr_Factory* factory, Mdr_InstanceId* instanceResult);

/**
    Destroy an instance.
    For each registered module, it calls the destruct function,
    in reverse order of registration.

    @param  factory         The factory at which the instance was created.
    @param  instance        The instance id that was returned when creating the instance.
**/
void Mdr_Destroy(Mdr_Factory* factory, Mdr_InstanceId instance);

/**
    Get a pointer to the modules data part of an instance.

    @param  module          The module to get the instance data for.
    @param  instance        The instance to get the data from.
**/
void* Mdr_GetModuleInstanceData(Mdr_ModuleId module, Mdr_InstanceId instance);

/**
    End header guard
**/
#endif // MDR_FACTORY_FUNCTIONS_H
