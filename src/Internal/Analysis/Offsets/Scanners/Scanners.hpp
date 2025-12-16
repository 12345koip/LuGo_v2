/*
This file was created by
12345koip for the LuGo executor
on 16/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include <map>
#include "libhat/include/libhat.hpp"
#include "Common/Attributes.hpp"

namespace LuGo::Analysis::Offsets::Scanners {
    namespace Luau {
        void Scan();
    }

    namespace RBX {
        void Scan();
    }
}