/*
This file was created by
12345koip for the LuGo executor
on 15/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include "Common/Attributes.hpp"
#include "Logger/Logger.hpp"

namespace LuGo::Analysis::Offsets {
    enum class PointerObfuscationType: uint8_t {
        Add,
        Subtract
    };

    struct ObfuscatedPointer {
        uintptr_t rawPtr;
        PointerObfuscationType obfuscationType;
        ptrdiff_t ptrOperand; //what the operation on the obfuscated pointer should be done with (e.g. subtract 0x??)

        void* Resolve() const {
            switch (this->obfuscationType) {
                case PointerObfuscationType::Add:
                    return reinterpret_cast<void*>(this->rawPtr + this->ptrOperand);

                case PointerObfuscationType::Subtract:
                    return reinterpret_cast<void*>(this->rawPtr - this->ptrOperand);

                default: {
                    LuGoLog("Unrecognised pointer obfuscation type - returning raw pointer", IO::OutputType::Warning);
                    return reinterpret_cast<void*>(this->rawPtr);
                }
            }
        }
    };
}