/*
This file was created by
12345koip for the LuGo executor
on 17/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include <string>
#include <unordered_map>
#include "Common/Attributes.hpp"
#include "RBX/TaskScheduler.hpp"
#include "RobloxJob.hpp"

namespace LuGo::Execution::Scheduling {
    struct RobloxJobVFTable {
        void(__fastcall* Destroy)(void* job);
        void(__fastcall* _unknown_0)(void* job);
        void(__fastcall* _unknown_1)(void* job);
        void(__fastcall* guard_check_)(void* job);
        bool(__fastcall* isJobEnabled)(void* job);
        int64_t(__fastcall* getMaxStackSize)(void* job);
        bool(__fastcall* step)(void* job, RBX::TaskScheduler::Job::Stats* stats);
    };

    //for clarity - this is the LuGo task scheduler, which
    //works around the scheduling of the Roblox task scheduler.
    class Scheduler final {
        private:
            std::unordered_map<const RobloxJobVFTable*, std::string> vtableNameMapping {};
            Scheduler();

        public:
            //quick lookup map of RTTI name to job enum.
            const std::unordered_map<std::string_view, RBXJobType> m_jobEnumLookupMap {
                {"RBX::Studio::DebuggerConnectionJob", RBXJobType::Studio_DebuggerConnectionJob},
                {"RBX::ModelMeshJob", RBXJobType::ModelMeshJob},
                {"RBX::ScriptContextFacets::GcJob", RBXJobType::ScriptContextFacets_GcJob},
                {"RBX::ScriptContextFacets::WaitingHybridScriptsJob", RBXJobType::ScriptContextFacets_WaitingHybridScriptsJob},
                {"RBX::HeartbeatTask", RBXJobType::HeartbeatTask},
                {"RBX::PhysicsJob", RBXJobType::PhysicsJob},
                {"RBX::NavigationService::PathUpdateJob", RBXJobType::NavigationService_PathUpdateJob},
                {"RBX::NagivationService::NavigationJob", RBXJobType::NagivationService_NavigationJob},
                {"RBX::GenericDataModelJob", RBXJobType::GenericDataModelJob},
                {"RBX::HttpRbxApiJob", RBXJobType::HttpRbxApiJob},
                {"RBX::PhysicsStepJob", RBXJobType::PhysicsStepJob}
            };



            static Scheduler& GetSingleton() {
                static Scheduler singleton;
                return singleton;
            }

            L_FORCEINLINE std::string GetJobNameFromVTable(const RobloxJobVFTable* vtable) const {
                return (this->vtableNameMapping.contains(vtable)? this->vtableNameMapping.at(vtable): "");
            }

            void OnRobloxJobStepped(void** job, const RBXJobType jobType, RBX::TaskScheduler::Job::Stats* metrics);
    };
}