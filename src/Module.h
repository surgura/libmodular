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
#include "Modular/Types.h"

/**
    Information about a registered module.
**/
typedef struct
{
    /**
        The function that is called when a new instance is instantiated.
        arg0    The id of this module.
        arg1    The id of the instance being created.
    **/
    void (*construct)(Mdr_ModuleId, Mdr_InstanceId);
    /**
        The function that is called when an instance is destroyed.
        arg0    The id of this module.
        arg1    The id of the instance being destroyed.
    **/
    void (*destruct)(Mdr_ModuleId, Mdr_InstanceId);
    /**
        The offset from a pointer to an instance, to the instance data of this module, in bytes.
    **/
    Mdr_U64 instanceOffset;
} Mdr_Module;

/**
    End header guard
**/
#endif // MDR_MODULE_H
