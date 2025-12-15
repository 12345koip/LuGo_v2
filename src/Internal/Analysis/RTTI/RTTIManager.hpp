/*
This file was created by
12345koip for the LuGo executor
on 15/12/2025. See LICENSE and README
for details.
*/

//This header file just provides a singleton wrapper around
//the RTTIHook dependency.

#pragma once

#include <unordered_map>
#include "Common/Attributes.hpp"
#include "RTTIHook/src/PE.h"
#include "RTTIHook/src/HookTemplates.h"
#include "RTTIHook/src/RTTIScanner.h"
#include "RTTIHook/src/VFTHook.h"

namespace LuGo::Analysis::RTTI {
    class RTTIManager final {
        private:
            std::unique_ptr<RTTIScanner> scannerInst;
            std::unordered_map<std::string, std::shared_ptr<VFTHook>> activeVFTHooks {};

            RTTIManager() {
                LuGoLog("Scanning for RTTI...", IO::OutputType::Info);
                this->scannerInst = std::make_unique<RTTIScanner>();
                this->scannerInst->scan();
                LuGoLog("RTTI scan complete!", IO::OutputType::Info);
            }

        public:
            static RTTIManager& GetSingleton() {
                static RTTIManager singleton;
                return singleton;
            }

            //NOTE: pass the UNMANGLED class name to this function
            L_NODISCARD L_FORCEINLINE std::shared_ptr<RTTIScanner::RTTI> GetRTTIForClass(const std::string_view& className) const {
                return std::shared_ptr<RTTIScanner::RTTI>(this->scannerInst->getClassRTTI(std::string(className)));
            }

            L_NOINLINE std::shared_ptr<VFTHook> HookVirtualFunction(const std::string_view className, const uint32_t vtableIndex, void* replacement) {
                if (this->activeVFTHooks.contains(std::string(className))) return nullptr;

                const auto& rttiForClass = this->GetRTTIForClass(className);
                if (!rttiForClass) return nullptr;

                auto hook = std::make_shared<VFTHook>(rttiForClass->pVirtualFunctionTable, vtableIndex, replacement);
                this->activeVFTHooks.emplace(className, hook);

                return hook;
            }

            L_NODISCARD std::shared_ptr<VFTHook> GetVFTHookForClass(const std::string_view className) const {
                return (this->activeVFTHooks.contains(std::string(className))? this->activeVFTHooks.at(std::string(className)): nullptr);
            };

            void RemoveHookForClass(const std::string_view className) {
                if (const auto it = this->activeVFTHooks.find(std::string(className)); it != this->activeVFTHooks.end())
                    this->activeVFTHooks.erase(it);
            };
    };
}