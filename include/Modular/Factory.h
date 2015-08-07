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
    The data of a factory instance.
**/
typedef struct
{
    /**
        The sum of the size of all registered modules' instances.
    **/
    u64 moduleInstancesSizeSum;

    /**
        List of registered modules.
        The data of the node consists of a module struct,
        followed by an arbitrarily sized piece of data for the module common data.
    **/
    Mdr_LinkedList modules;

    /**
        List of instances.
    **/
    Mdr_LinkedList instances;
} Mdr_Factory;

/**
    End header guard
**/
#endif // MDR_FACTORY_H
