/*
This file was created by
12345koip for the LuGo executor
on 18/12/2025. See LICENSE and README
for details.
*/

#include <windows.h>
#include "DataModel.hpp"

using namespace LuGo::Analysis;
using namespace RBX;


static bool IsDataModelPointerValid(void* dataModel) {
    if (!dataModel) return false;

    MEMORY_BASIC_INFORMATION info {};
    const SIZE_T result = VirtualQuery(dataModel, &info, sizeof(info));
    if (!result) return false;

    const bool isLargeEnough = info.RegionSize > 0x96f;
    const bool notReserved = !(info.State & MEM_RESERVE);
    const bool validType = (info.Type == MEM_IMAGE) || (info.Type == MEM_MAPPED) || (info.Type == MEM_PRIVATE);


    return isLargeEnough && notReserved && validType;
}

Studio::StudioGameStateType DataModel::GetGameStateType(DataModel* self) {
    if (!IsDataModelPointerValid(self)) return Studio::StudioGameStateType_Null;

    const auto& OffsetManager = Offsets::OffsetManager::GetSingleton();
    const auto func = reinterpret_cast<Studio::StudioGameStateType(__fastcall*)(DataModel* self)>(OffsetManager.GetPointerOffset(Offsets::RawPointerOffsetRef::RBX_DataModel_GetGameStateType));

    return func(self);
}