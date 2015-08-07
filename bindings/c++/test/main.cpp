#include <ModularCpp/Factory.hpp>

// needed for printf
#include <stdio.h>

// needed for generating a random number
#include <stdlib.h>

#include <string>
#include <iostream>

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
    MyModuleInstance* myModuleInstance = Modular::Factory::GetModuleInstanceData<MyModuleInstance>(module, instance);

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
    MyModuleInstance* myModuleInstance = Modular::Factory::GetModuleInstanceData<MyModuleInstance>(module, instance);

    // all MyModuleInstances have a common MyModule object.
    // Lets also show the number contained in there so we can prove this.
    MyModule* myModule = Modular::Factory::GetModuleCommonData<MyModule>(module);

    // show the instance number and common object number.
    printf("Destructing MyModuleInstance. myInstanceNumber: %d myCommonNumber: %d\n",
           myModuleInstance->myInstanceNumber,
           myModule->myCommonNumber);
}

int main()
{
    Modular::Factory factory;

    Mdr_ModuleId myModuleId;
    try
    {
        myModuleId = factory.Register(sizeof(MyModule), sizeof(MyModuleInstance), &MyModuleConstruct, &MyModuleDestruct);
    }
    catch (Mdr_Result)
    {
        return -1;
    }

    MyModule* myModule = factory.GetModuleCommonData<MyModule>(myModuleId);
    myModule->myCommonNumber = 1234;

    Mdr_InstanceId instance1;
    try
    {
        instance1 = factory.Instantiate();
    }
    catch (Mdr_Result)
    {
        return -1;
    }

    Mdr_InstanceId instance2;
    try
    {
        instance2 = factory.Instantiate();
    }
    catch (Mdr_Result)
    {
        return -1;
    }

    factory.Destroy(instance1);
    factory.Destroy(instance2);

    while(1){}

    return 0;
}
