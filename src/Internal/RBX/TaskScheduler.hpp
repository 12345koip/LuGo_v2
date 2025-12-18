/*
This file was created by
12345koip for the LuGo executor
on 17/12/2025. See LICENSE and README
for details.
*/

#pragma once
#include <cstdint>
#include "ScriptContext.hpp"
#include "DataModel.hpp"

namespace RBX {
    struct Time {
        double sec;
    };

    namespace TaskScheduler {
        namespace Job {

            struct Stats {
                Time timeNow;
                Time timespanSinceLastStep;
                Time timespanOfLastStep;
            };

        }
    }

    namespace ScriptContextFacets {
        struct WaitingHybridScriptsJob {
            char _pad0[0x1D8];
            DataModel* dataModel;
            char _pad1[0x18];
            ScriptContext* scriptContext;
        };
    }
}