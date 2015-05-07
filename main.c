#include "LibModular/Factory.h"
#include <stdio.h>

typedef struct
{
} Script;

typedef struct
{
    int a;
} ScriptInstance;

void ScriptInstantiate(void* userData, void* instance)
{
    printf("create");
}

void ScriptDelete(void* userData, void* instance)
{
    printf("delete");
}

int main()
{
    Mdr_Factory factory;
    Mdr_ConstructFactory(&factory);

    Script script;
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
