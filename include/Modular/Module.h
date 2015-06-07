/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Header guard
**/
#ifndef MDR_Module_H
#define MDR_Module_H

/**
    Include files
**/
#include "Types.h"

/**
    Information about a registered module.
**/
typedef struct
{
    /**
        The function that is called when a new instance is instantiated.
        void* arg0      A pointer to the common object
        void* arg1      A pointer to the module instance object
    **/
    void (*construct)(Mdr_ModuleId, Mdr_InstanceId);
    /**
        The function that is called when an instance is destroyed.
        void* arg0      A pointer to the common object
        void* arg1      A pointer to the module instance object
    **/
    void (*destruct)(Mdr_ModuleId, Mdr_InstanceId);
    /**
        The offset from the pointer to an instance an instance of this module is stored in bytes.
    **/
    u64 instanceOffset;
} Mdr_Module;

/**
    End header guard
**/
#endif // MDR_MODULE_H
