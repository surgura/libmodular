#include "Modular/FactoryFunctions.h"

#include <stdio.h>

typedef struct
{
} ScriptModule;

typedef struct
{
    int test;
} ScriptInstance;

void ScriptConstruct(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    printf("Script construct");
    // Initialize script stuff
    ScriptInstance* scriptinstance = Mdr_GetModuleInstanceData(module, instance);
    scriptinstance->test = 15;
}

void ScriptDestruct(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    printf("Script destruct");
    // Remove script stuff
}

void RegisterScriptFunction(ScriptModule* module, ScriptInstance* instance, const char* functionName)
{
    // Do stuff
    printf("\n%d\n", instance->test);
}


typedef struct
{
} GUIModule;

typedef struct
{

} GUIInstance;

void GUIConstruct(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    printf("GUI construct");
    // Initialize gui stuff
}

void GUIDestruct(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    printf("GUI destruct");
    // Remove gui stuff
}


typedef struct
{
    Mdr_ModuleId script;
} GUIScriptModule;

typedef struct
{

} GUIScriptInstance;

void GUIScriptConstruct(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    printf("GUIScript construct");
    // Register a function at script!
    GUIScriptModule* guiscript = Mdr_GetModuleCommonData(module);
    ScriptInstance* scriptInstance = Mdr_GetModuleInstanceData(guiscript->script, instance);
    ScriptModule* scriptModule = Mdr_GetModuleCommonData(guiscript->script);

    RegisterScriptFunction(scriptModule, scriptInstance, "Test");
}

void GUIScriptDestruct(Mdr_ModuleId module, Mdr_InstanceId instance)
{
    printf("GUIScript destruct");
}

int main()
{
    Mdr_Factory factory;
    Mdr_Initialize(&factory);

    Mdr_ModuleId script;
    Mdr_Register(&factory, &script, sizeof(ScriptModule), sizeof(ScriptInstance), &ScriptConstruct, &ScriptDestruct);
    ScriptModule* scriptModule = Mdr_GetModuleCommonData(script);

    Mdr_ModuleId gui;
    Mdr_Register(&factory, &gui, sizeof(GUIModule), sizeof(GUIInstance), &GUIConstruct, &GUIDestruct);
    GUIModule* guiModule = Mdr_GetModuleCommonData(gui);

    Mdr_ModuleId guiscript;
    Mdr_Register(&factory, &guiscript, sizeof(GUIScriptModule), sizeof(GUIScriptInstance), &GUIScriptConstruct, &GUIScriptDestruct);
    GUIScriptModule* guiscriptcommondata = Mdr_GetModuleCommonData(guiscript);
    guiscriptcommondata->script = script;




    while(1)
    {

    }
//    Mdr_Module gui = Mdr_Register(&factory, sizeof(GUIModule), sizeof(GUIInstance), &GUIConstruct, &GUIDestruct);
//    Mdr_Module guiscript = Mdr_Register(&factory, sizeof(GUIScriptModule), sizeof(GUIScriptInstance), &GUIScriptConstruct, &GUIScriptDestruct);

    return 0;
}
