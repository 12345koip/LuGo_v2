/*
This file was created by
12345koip for the LuGo executor
on 14/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include "Capstone/include/capstone/capstone.h"
#include "Common/Attributes.hpp"


namespace LuGo::Analysis {

    struct AsmOperand {
        int type;
        int64_t disp;
        int64_t imm;
        x86_reg reg;
        x86_reg base;
        x86_reg index;
        int scale;
    };

}