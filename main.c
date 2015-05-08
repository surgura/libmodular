#include "LibModular/Factory.h"
#include <stdio.h>

typedef struct
{
    int a;
} Script;

typedef struct
{
} ScriptInstance;

void ScriptInstantiate(void* userData, void* instance)
{
    printf("create\n");
}

void ScriptDelete(void* userData, void* instance)
{
    printf("delete\n");
    //printf("%d\n", ((Script*)userData)->a);
}

int main()
{
    Mdr_Factory factory;
    Mdr_ConstructFactory(&factory);

    Script script;
    //script.a = 3;
    ModuleID* scriptId;
    Mdr_RegisterModule(&factory, &scriptId, &script, sizeof(ScriptInstance), &ScriptInstantiate, &ScriptDelete);
    Mdr_RegisterModule(&factory, &scriptId, &script, sizeof(ScriptInstance), &ScriptInstantiate, &ScriptDelete);
    Mdr_RegisterModule(&factory, &scriptId, &script, sizeof(ScriptInstance), &ScriptInstantiate, &ScriptDelete);

    InstanceID* instanceId;
    Mdr_Instantiate(&factory, &instanceId);
    Mdr_Instantiate(&factory, &instanceId);

    Mdr_DestructFactory(&factory);

    return 0;
}
