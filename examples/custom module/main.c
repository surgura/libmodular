#ifndef MY_MODULE_H
#define MY_MODULE_H

// main header for LibModular
#include "Modular/Modular.h"

// needed for printf
#include <stdio.h>

// needed for generating a random number
#include <stdlib.h>

// this struct will be shared between all module instances
typedef struct
{
    int myCommonNumber;
} MyModule;

// each instance have its own object of this struct
typedef struct
{
    int myInstanceNumber;
} MyModuleInstance;

// construct an instance.
// we get passed the id of the module we are constructing an instance(MyModuleInstance) for
// and the id of the factories instances, so we can request our own little part from it(which thus is MyModuleInstance).
void MyModuleConstruct(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    // we can do some fun stuff with our new instance.
    // first, get the instance
    MyModuleInstance* myModuleInstance = Mdr_GetModuleInstanceData(module, instance);

    // say we want to assign some random integer
    // we will later show this when we destruct our instance, just so we can identify between two instances.
    myModuleInstance->myInstanceNumber = rand() % 100;

    // show the number
    printf("Constructing MyModuleInstance. myInstanceNumber: %d\n", myModuleInstance->myInstanceNumber);
}

// this function is pretty much the same as ModuleConstruct, except it is called when our instance should be destructed.
void MyModuleDestruct(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    // we want to show the number we assigned earlier at constructing.
    // get the instance
    MyModuleInstance* myModuleInstance = Mdr_GetModuleInstanceData(module, instance);

    // all MyModuleInstances have a common MyModule object.
    // Lets also show the number contained in there so we can prove this.
    MyModule* myModule = Mdr_GetModuleCommonData(module);

    // show the instance number and common object number.
    printf("Destructing MyModuleInstance. myInstanceNumber: %d myCommonNumber: %d\n",
           myModuleInstance->myInstanceNumber,
           myModule->myCommonNumber);
}

int main()
{
    // initialize a factory object
    Mdr_Factory factory;
    Mdr_Initialize(&factory);

    // tell the factory we want it to use our module
    Mdr_ModuleId myModuleId;
    Mdr_Register(&factory, &myModuleId, sizeof(MyModule), sizeof(MyModuleInstance), &MyModuleConstruct, &MyModuleDestruct);

    // we can request the common data between all module instances.
    MyModule* myModule = Mdr_GetModuleCommonData(myModuleId);
    // lets assign its number so we can prove its common between all instances
    myModule->myCommonNumber = 1234;

    // tell the factory to create an instance.
    // this actually calls the construct function for every registered module in order of registration.
    // however, we have only one registered.
    Mdr_InstanceId instance;
    Mdr_Instantiate(&factory, &instance);

    // lets create another one so we can see they use a different MyModuleInstance
    Mdr_InstanceId instance2;
    Mdr_Instantiate(&factory, &instance2);

    // destroy the instances.
    // this calls the destruct function in reverse order of registration.
    Mdr_Destroy(&factory, instance);
    Mdr_Destroy(&factory, instance2);

    // we just loop so we can easily read the output
    while(1)
    {

    }

    return 0;
}

#endif // MY_MODULE_H
