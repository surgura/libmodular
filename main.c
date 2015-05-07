#include "LibModular/Factory.h"
#include <stdio.h>

typedef struct
{
} Script;

typedef struct
{
} ScriptInstance;

void ScriptInstantiate(void* userData, void* instance)
{

}

void ScriptDelete(void* userData, void* instance)
{

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

    Mdr_DestructFactory(&factory);

    return 0;
}
