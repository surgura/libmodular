#include "LibModular/Factory.h"
#include <stdio.h>

typedef struct
{
} Script;

typedef struct
{
    int myint;
} ScriptInstance;

void ScriptInstantiate(void* userData, void* instance)
{
    ((ScriptInstance*)instance)->myint = 50;
}

void ScriptDelete(void* userData, void* instance)
{
}

typedef struct
{
    Mdr_Factory* factory;
    ModuleID scriptId;
} ScriptUser;

typedef struct
{
} ScriptUserInstance;

void ScriptUserInstantiate(void* userData, void* instance)
{
    ScriptUser* scriptUser = (ScriptUser*)userData;
    ScriptInstance* scriptInstance;
    if(Mdr_GetLatestModuleInstance(scriptUser->factory, (void**)&scriptInstance, scriptUser->scriptId) < 0)
    {
        printf("crashycrashy\n");
    }

    printf("%d\n", scriptInstance->myint);
}

void ScriptUserDelete(void* userData, void* instance)
{

}

int main()
{
    Mdr_Factory factory;
    Mdr_ConstructFactory(&factory);

    Script script;
    ModuleID scriptId;
    Mdr_RegisterModule(&factory, &scriptId, &script, sizeof(ScriptInstance), &ScriptInstantiate, &ScriptDelete);

    ScriptUser scriptUser;
    scriptUser.factory = &factory;
    scriptUser.scriptId = scriptId;
    ModuleID scriptUserId;
    Mdr_RegisterModule(&factory, &scriptUserId, &scriptUser, sizeof(ScriptUserInstance), &ScriptUserInstantiate, &ScriptUserDelete);

    InstanceID instanceId;
    Mdr_Instantiate(&factory, &instanceId);

    Mdr_DestructFactory(&factory);

    return 0;
}
