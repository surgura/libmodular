/**
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    @author Aart Stuurman
**/

/**
    Header guard
**/
#ifndef MDRCPP_FACTORY_H
#define MDRCPP_FACTORY_H

/**
    Include files
**/
extern "C"
{
#include <Modular/Modular.h>
}
#include <iostream>

namespace Modular
{

/**
    Contains the data of a modular factory object.
    Has all functions to interact with it.
**/
class Factory
{
private:
    Mdr_Factory factory;
public:
    Factory()
    {
        Mdr_Initialize(&factory);
    }

    ~Factory()
    {
        Mdr_Cleanup(&factory);
    }

    /**
        Binding for the Mdr_Register function.
        @param  moduleSize      As the original argument.
        @param  instanceSize    As the original argument.
        @param  construct       As the original argument.
        @param  destruct        As the original argument.
        @return                 As the original moduleResult argument, but as a direct return value.
        @throw  Mdr_Result      As the original return value.
    **/
    Mdr_ModuleId Register(u32 moduleSize, u32 instanceSize, void (*construct)(Mdr_ModuleId, Mdr_InstanceId), void (*destruct)(Mdr_ModuleId, Mdr_InstanceId))
    {
        Mdr_ModuleId moduleId;
        if (Mdr_Register(&factory, &moduleId, moduleSize, instanceSize, construct, destruct) == MDR_ALLOC_ERROR)
            throw MDR_ALLOC_ERROR;
        return moduleId;
    }

    /**
        Binding for the Mdr_GetModuleCommonData function.
        @param  module          As the original argument.
        @return                 As the original return value.
    **/
    template <typename CommonDataType>
    static CommonDataType* GetModuleCommonData(Mdr_ModuleId module)
    {
        return static_cast<CommonDataType*>(Mdr_GetModuleCommonData(module));
    }

    /**
        Binding for the Mdr_Instantiate function.
        @return                 As the original instanceResult argument, but as a direct return value.
        @throw  Mdr_Result      As the original return value.
    **/
    Mdr_InstanceId Instantiate()
    {
        Mdr_InstanceId instanceId;
        if (Mdr_Instantiate(&factory, &instanceId) == MDR_ALLOC_ERROR)
            throw MDR_ALLOC_ERROR;
        return instanceId;
    }

    /**
        Binding for the Mdr_Destroy function.
        @param  instance        As the original argument.
    **/
    void Destroy(Mdr_InstanceId instance)
    {
        Mdr_Destroy(&factory, instance);
    }

    /**
        Binding for the Mdr_GetModuleInstanceData function.
        @param  module          As the original argument.
        @param  instance        As the original argument.
        @return                 As the original return value.
    **/
    template <typename ModuleInstanceType>
    static ModuleInstanceType* GetModuleInstanceData(Mdr_ModuleId module, Mdr_InstanceId instance)
    {
        return static_cast<ModuleInstanceType*>(Mdr_GetModuleInstanceData(module, instance));
    }
};

}

/**
    End header guard
**/
#endif // MDRCPP_FACTORY_H
