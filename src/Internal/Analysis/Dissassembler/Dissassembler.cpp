/*
This file was created by
12345koip for the LuGo executor
on 14/12/2025. See LICENSE and README
for details.
*/

#include <algorithm>
#include <span>
#include <iterator>
#include "Dissassembler.hpp"
#include "IO/Logger.hpp"

using namespace LuGo::Analysis;

Dissassembler::Dissassembler() {
    const cs_err openStatus = cs_open(CS_ARCH_X86, CS_MODE_64, &this->csHandle);

    if (openStatus != CS_ERR_OK) {
        LuGoLog("Could not initialise dissassembler! Cannot proceed!", IO::OutputType::Error);
        throw std::runtime_error("failed to initialise dissassembler");
    }

    //enable dissassembly detail.
    const cs_err detailStatus = cs_option(this->csHandle, CS_OPT_DETAIL, CS_OPT_ON);
    if (detailStatus != CS_ERR_OK) {
        LuGoLog("Could not initialise dissassembler! Cannot proceed!", IO::OutputType::Error);
        throw std::runtime_error("failed to initialise dissassembler");
    }
}

Dissassembler::~Dissassembler() {
    cs_close(&this->csHandle);
}

std::optional<AsmInstructionList> Dissassembler::Dissassemble(const uint8_t* start, const uint8_t* end) const {
    const auto startAddress = reinterpret_cast<uintptr_t>(start);
    const auto endAddress = reinterpret_cast<uintptr_t>(end);
    const ptrdiff_t blockSize = end - start;


    cs_insn* rawDisasm;
    const size_t instructionCount = cs_disasm(
        this->csHandle,
        start,
        blockSize,
        startAddress,
        endAddress,
        &rawDisasm
    );

    if (!instructionCount) return std::nullopt;

    //we must copy the disassembled data into our own structs.
    std::vector<AsmInstruction> copiedInstructions {};
    copiedInstructions.reserve(instructionCount);

    for (size_t i = 0; i < instructionCount; ++i) {
        const cs_insn& instruction = rawDisasm[i];
        std::vector<uint8_t> insBytes (instruction.bytes, instruction.bytes + instruction.size);

        //copy operand detail, if present.
        std::vector<AsmOperand> detail;

        if (instruction.detail) {
            detail.reserve(instruction.detail->x86.op_count);

            std::ranges::transform(
                std::span(instruction.detail->x86.operands, instruction.detail->x86.op_count),
                std::back_inserter(detail), [](const cs_x86_op& op) -> AsmOperand {
                    return AsmOperand {
                        op.type, op.mem.disp, op.imm,
                        op.reg, op.mem.base, op.mem.index, op.mem.scale
                    };
                }
            );
        }

        copiedInstructions.emplace_back(
            instruction.mnemonic,
            instruction.op_str,
            instruction.address,
            instruction.size,
            std::move(insBytes),
            std::move(detail),
            static_cast<x86_insn>(instruction.id)
        );
    }

    cs_free(rawDisasm, instructionCount);
    return AsmInstructionList {copiedInstructions};
}