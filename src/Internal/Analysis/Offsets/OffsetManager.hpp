/*
This file was created by
12345koip for the LuGo executor
on 15/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include <map>
#include <unordered_map>
#include "Common/Attributes.hpp"
#include "PointerObfuscation.hpp"

namespace LuGo::Analysis::Offsets {

    enum class RawPointerOffsetRef: uint8_t {
        luaC_step,
        luaC_fullgc,
        luaH_new,

        RBX_Instance_PushInstance,
        RBX_ScriptContext_ResumeImpl,
        RBX_ScriptContext_GetGlobalState,
        RBX_DataModel_GetGameStateType
    };

    constexpr const char* RawPointerOffsetRefToString(const RawPointerOffsetRef ref) {
        switch (ref) {
            case RawPointerOffsetRef::luaC_step:                        return "luaC_step";
            case RawPointerOffsetRef::luaC_fullgc:                      return "luaC_fullgc";
            case RawPointerOffsetRef::luaH_new:                         return "luaH_new";
            case RawPointerOffsetRef::RBX_Instance_PushInstance:        return "Instance::PushInstance";
            case RawPointerOffsetRef::RBX_ScriptContext_ResumeImpl:     return "ScriptContext::resumeImpl";
            case RawPointerOffsetRef::RBX_ScriptContext_GetGlobalState: return "ScriptContext::GetGlobalState";
            case RawPointerOffsetRef::RBX_DataModel_GetGameStateType:   return "DataModel::getGameStateType";
            default:                                                    return "UNKNOWN";
        }
    }

    enum class ObfuscatedPointerRef: uint8_t {
        ScriptContext, //for ScriptContext::resumeImpl.
    };

    constexpr const char* ObfuscatedPointerRefToString(const ObfuscatedPointerRef ref) {
        switch (ref) {
            case ObfuscatedPointerRef::ScriptContext: return "ScriptContext";
            default:                                  return "UNKNOWN";
        }
    }


    class OffsetManager final {
        private:
            std::unordered_map<RawPointerOffsetRef, uintptr_t> rawPointerOffsets {};
            std::unordered_map<ObfuscatedPointerRef, std::shared_ptr<ObfuscatedPointer>> obfuscatedPointers {};
            std::unordered_map<std::string_view, void*> fflagMap {}; //we would only ever view string literals already in the binary.

            OffsetManager() = default;

        public:
            static OffsetManager& GetSingleton() {
                static OffsetManager singleton;
                return singleton;
            }

            L_NODISCARD L_FORCEINLINE std::shared_ptr<ObfuscatedPointer> GetPointerObfuscation(const ObfuscatedPointerRef ref) const {
                return (this->obfuscatedPointers.contains(ref)? this->obfuscatedPointers.at(ref): nullptr);
            }

            void SetPointerObfuscation(const ObfuscatedPointerRef ref, const std::shared_ptr<ObfuscatedPointer> offset) {
                this->obfuscatedPointers.emplace(ref, offset);
            }

            L_NODISCARD L_FORCEINLINE uintptr_t GetPointerOffset(const RawPointerOffsetRef ref) const {
                return (this->rawPointerOffsets.contains(ref)? this->rawPointerOffsets.at(ref): 0x00);
            }

            L_FORCEINLINE void SetPointerOffset(const RawPointerOffsetRef ref, const uintptr_t offset) {
                this->rawPointerOffsets.emplace(ref, offset);
            }

            L_FORCEINLINE void AddFastFlag(const std::string_view& key, void* valAddress) {
                if (!this->fflagMap.contains(key))
                    this->fflagMap.emplace(key, valAddress);
            }

            template<typename T> T* GetFastFlagPointer(const std::string_view& flagName) {
                return static_cast<T*>(this->fflagMap.contains(flagName)? this->fflagMap.at(flagName): nullptr);
            }
    };
}