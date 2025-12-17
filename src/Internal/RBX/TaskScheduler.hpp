/*
This file was created by
12345koip for the LuGo executor
on 17/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include <cstdint>

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
}