/*
This file was created by
12345koip for the LuGo executor
on 14/12/2025. See LICENSE and README
for details.
*/

#include "AsmInstructionList.hpp"

using namespace LuGo::Analysis;


bool AsmInstructionList::HasInstruction(const std::string_view& mnemonic, const std::string_view& operandStr) const {
    const auto elementIt = std::ranges::find_if(this->instructions.begin(), this->instructions.end(), [&](const auto& otherIns) -> bool {
        return otherIns.mnemonic == mnemonic && otherIns.operands.find(operandStr) != std::string::npos;
    });

    return elementIt != this->instructions.end();
}

const AsmInstruction* AsmInstructionList::GetInstructionWhichMatches(const std::string_view& mnemonic, const std::string_view& operandStr) const {
    const AsmInstruction* returnIns = nullptr;

    for (const auto& ins: this->instructions) {
        if (ins.mnemonic == mnemonic && ins.operands.find(operandStr) != std::string::npos) {
            returnIns = &ins;
            break;
        }
    }

    return returnIns; //if not found, the caller can handle that case.
}

const AsmInstruction* AsmInstructionList::GetInstructionWhichMatches(const x86_insn opcode, const std::string_view& operandStr) const {
    const AsmInstruction* returnIns = nullptr;

    for (const auto& ins: this->instructions) {
        if (ins.opcode == opcode && ins.operands.find(operandStr) != std::string::npos) {
            returnIns = &ins;
            break;
        }
    }

    return returnIns; //once again, the caller can handle null cases.
}

const std::vector<const AsmInstruction*> AsmInstructionList::GetAllInstructionsWhichMatch(const std::string_view& mnemonic, const std::string_view& operandStr) const {
    std::vector<const AsmInstruction*> matches;

    for (const auto& ins: this->instructions) {
        if (ins.mnemonic == mnemonic && ins.operands.find(operandStr) != std::string::npos)
            matches.push_back(&ins);
    }

    return matches;
}


const std::vector<const AsmInstruction*> AsmInstructionList::GetAllInstructionsWhichMatch(const x86_insn opcode, const std::string_view& operandStr) const {
    std::vector<const AsmInstruction*> matches;

    for (const auto& ins: this->instructions) {
        if (ins.opcode == opcode && ins.operands.find(operandStr) != std::string::npos)
            matches.push_back(&ins);
    }

    return matches;
}