/*
This file was created by
12345koip for the LuGo executor
on 18/12/2025. See LICENSE and README
for details.
*/

#pragma once
#include "Analysis/Offsets/OffsetManager.hpp"
#include "DataModel.hpp"
#include "Luau/VM/include/lua.h"

namespace RBX {
    //this is mostly a struct so it can be used as pointer, of course we won't
    //store a mock class or our own pointer so one must be provided to call the
    //roblox methods.
    struct ScriptContext {
        static lua_State* GetGlobalState(void* self);
        static DataModel* GetDataModel(void* self);
    };
}