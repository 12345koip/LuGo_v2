/*
This file was created by
12345koip for the LuGo executor
on 14/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include <optional>
#include "Capstone/include/capstone/capstone.h"
#include "AsmInstructionList.hpp"
#include "AsmInstruction.hpp"


namespace LuGo::Analysis {

    class Dissassembler final {
        private:
            csh csHandle;
            Dissassembler();
            ~Dissassembler();

        public:
            std::optional<AsmInstructionList> Dissassemble(const uint8_t* start, const uint8_t* end) const;

            //WARNING: this WILL run until the next occurence of a byte
            //which is deemed to signify function end, which means this
            //could run haywire if misused!! thanks c:
            static uint8_t* GetFunctionEnd(uint8_t* currAddress) {
                while (true) {
                    ++currAddress;
                    uint8_t& insByte = *currAddress;

                    if (insByte == 0xC3 || //ret
                            insByte == 0xC2 || //ret imm16
                            insByte == 0xCC || //int3
                            insByte == 0x90) //nop
                        return currAddress;
                }
            }
    };

}