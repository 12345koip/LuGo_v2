/*
This file was created by
12345koip for the LuGo executor
on 14/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include "Capstone/include/capstone/capstone.h"
#include "AsmOperand.hpp"
#include <cstdint>
#include <string>
#include <vector>


namespace LuGo::Analysis {

    struct AsmInstruction final {
        std::string mnemonic;
        std::string operands;
        uint64_t address;
        size_t size;
        x86_insn opcode;
        std::vector<uint8_t> bytes;
        std::vector<AsmOperand> detail;

        AsmInstruction(const std::string_view& mn, const std::string_view& op, uintptr_t add, uint64_t sz, std::vector<uint8_t> bytes, std::vector<AsmOperand> detail, x86_insn id):
            mnemonic(mn), operands(op), address(add), size(sz), bytes(std::move(bytes)), detail(std::move(detail)), opcode(id) {}
    };

}