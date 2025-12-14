/*
This file was created by
12345koip for the LuGo executor
on 14/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include "AsmInstruction.hpp"
#include "Common/Attributes.hpp"
#include <stdexcept>

namespace LuGo {
    namespace Analysis {

        class AsmInstructionList final {
            private:
                std::vector<AsmInstruction> instructions;

            public:
                AsmInstructionList(AsmInstructionList&&) = default;
                AsmInstructionList() = default;
                explicit AsmInstructionList(const std::vector<AsmInstruction>& move): instructions(move) {};


                //we will allow standard iteration over the class.
                L_NODISCARD inline auto begin() const noexcept {return this->instructions.begin();}
                L_NODISCARD inline auto end() const noexcept {return this->instructions.end();}
                L_NODISCARD inline auto rbegin() const noexcept {return this->instructions.rbegin();}
                L_NODISCARD inline auto rend() const noexcept {return this->instructions.rend();}
                L_NODISCARD inline size_t size() const noexcept {return this->instructions.size();}

                //other methods.
                bool HasInstruction(const std::string_view& mnemonic, const std::string_view& operandStr) const;

                const AsmInstruction* GetInstructionWhichMatches(const std::string_view& mnemonic, const std::string_view& operandStr) const;
                const AsmInstruction* GetInstructionWhichMatches(const x86_insn opcode, const std::string_view& operandStr) const;

                const std::vector<const AsmInstruction*> GetAllInstructionsWhichMatch(const std::string_view& mnemonic, const std::string_view& operandStr) const;
                const std::vector<const AsmInstruction*> GetAllInstructionsWhichMatch(const x86_insn opcode, const std::string_view& operandStr) const;

                //direct indexing.
                L_FORCEINLINE const AsmInstruction* operator[](const uint64_t i) const {
                    if (i - 1 > this->instructions.size())
                        throw std::runtime_error("index out of range");

                    return &this->instructions[i];
                }
        };

    }
}