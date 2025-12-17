/*
This file was created by
12345koip for the LuGo executor
on 15/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include "Common/Attributes.hpp"
#include "IO/Logger.hpp"

namespace LuGo::Analysis::Offsets {

    //NOTE: the add and subtract enums here depend entirely on
    //the assembly opcode used. For example, you can have an add
    //instruction with a negative operand if that is what the assembly
    //used. Subtract enum obfuscation types are usually only emitted from
    //"sub" asm instructions.
    enum class PointerObfuscationType: uint8_t {
        Add,
        Subtract
    };

    struct ObfuscatedPointer {
        PointerObfuscationType obfuscationType;
        ptrdiff_t ptrOperand; //what the operation on the obfuscated pointer should be done with (e.g. subtract 0x??)

        //Returns the unobfuscated pointer.
        void* DeobfuscatePointer(void* obfuscatedPtr) const {
            auto ptrOp = reinterpret_cast<uintptr_t>(obfuscatedPtr);

            switch (this->obfuscationType) {
                case PointerObfuscationType::Add:
                    return reinterpret_cast<void*>(ptrOp + this->ptrOperand);

                case PointerObfuscationType::Subtract:
                    return reinterpret_cast<void*>(ptrOp - this->ptrOperand);

                default: {
                    LuGoLog("Unrecognised pointer obfuscation type - returning raw pointer", IO::OutputType::Warning);
                    return obfuscatedPtr;
                }
            }
        }

        //Returns the obfuscated pointer.
        void* ObfuscatePointer(void* rawPtr) const {
            auto ptrOp = reinterpret_cast<uintptr_t>(rawPtr);

            switch (this->obfuscationType) {
                case PointerObfuscationType::Add:
                    return reinterpret_cast<void*>(ptrOp - this->ptrOperand);

                case PointerObfuscationType::Subtract:
                    return reinterpret_cast<void*>(ptrOp + this->ptrOperand);

                default: {
                    LuGoLog("Unrecognised pointer obfuscation type - returning obfuscated pointer", IO::OutputType::Warning);
                    return rawPtr;
                }
            }
        }
    };
}