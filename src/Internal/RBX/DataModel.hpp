/*
This file was created by
12345koip for the LuGo executor
on 18/12/2025. See LICENSE and README
for details.
*/

#pragma once
#include "Analysis/Offsets/OffsetManager.hpp"

namespace RBX {
    namespace Studio {
        enum StudioGameStateType: uint8_t {
            StudioGameStateType_Edit,
            StudioGameStateType_PlayClient,
            StudioGameStateType_PlayServer,
            StudioGameStateType_Standalone,
            StudioGameStateType_Null
        };
    }

    //same as ScriptContext, mostly a mock struct.
    struct DataModel {
        static Studio::StudioGameStateType GetGameStateType(DataModel* self);
    };
}