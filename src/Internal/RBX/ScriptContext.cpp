/*
This file was created by
12345koip for the LuGo executor
on 18/12/2025. See LICENSE and README
for details.
*/

#include "ScriptContext.hpp"

using namespace RBX;
using namespace LuGo::Analysis::Offsets;

DataModel* ScriptContext::GetDataModel(void* self) {
    const auto& OffsetManager = OffsetManager::GetSingleton();
    const auto func = reinterpret_cast<DataModel*(__fastcall*)(void* self)>(OffsetManager.GetPointerOffset(RawPointerOffsetRef::RBX_ScriptContext_GetDataModel));

    return func(self);
}

lua_State* ScriptContext::GetGlobalState(void* self) {
    const auto& OffsetManager = OffsetManager::GetSingleton();
    const auto func = reinterpret_cast<lua_State*(__fastcall*)(void*, const uint64_t*, const uint64_t*)>(OffsetManager.GetPointerOffset(RawPointerOffsetRef::RBX_ScriptContext_GetGlobalState));

    constexpr uint64_t script = 0ull;
    constexpr uint64_t identity = 0ull;
    return func(self, &script, &identity);
}