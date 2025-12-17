/*
This file was created by
12345koip for the LuGo executor
on 17/12/2025. See LICENSE and README
for details.
*/

#include "Scheduler.hpp"
#include "IO/Logger.hpp"
#include "Analysis/RTTI/RTTIManager.hpp"
#include "Execution/RBXHooks/RBXHooks.hpp"
#include "RBX/TaskScheduler.hpp"

using namespace LuGo::Execution::Scheduling;
using namespace LuGo::Analysis;

//the stepping of LuGo jobs relies on the stepping of Roblox jobs,
//hence why the constructor just hooks jobs.
Scheduler::Scheduler() {
    LuGoLog("Initialising LuGo scheduler: hooking Roblox DataModel jobs...", IO::OutputType::Info);
    auto& RTTIManager = RTTI::RTTIManager::GetSingleton();

    const std::unordered_map<std::string, std::shared_ptr<RTTIScanner::RTTI>> rttiMap = {
        {"RBX::Studio::DebuggerConnectionJob", RTTIManager.GetRTTIForClass("RBX::Studio::DebuggerConnectionJob")},
        {"RBX::ModelMeshJob", RTTIManager.GetRTTIForClass("RBX::ModelMeshJob")},
        {"RBX::ScriptContextFacets::GcJob", RTTIManager.GetRTTIForClass("RBX::ScriptContextFacets::GcJob")},
        {"RBX::ScriptContextFacets::WaitingHybridScriptsJob", RTTIManager.GetRTTIForClass("RBX::ScriptContextFacets::WaitingHybridScriptsJob")},
        {"RBX::HeartbeatTask", RTTIManager.GetRTTIForClass("RBX::HeartbeatTask")},
        {"RBX::PhysicsJob", RTTIManager.GetRTTIForClass("RBX::PhysicsJob")},
        {"RBX::NavigationService::PathUpdateJob", RTTIManager.GetRTTIForClass("RBX::NavigationService::PathUpdateJob")},
        {"RBX::NavigationService::NavigationJob", RTTIManager.GetRTTIForClass("RBX::NavigationService::NavigationJob")},
        {"RBX::GenericDataModelJob", RTTIManager.GetRTTIForClass("RBX::GenericDataModelJob")},
        {"RBX::HttpRbxApiJob", RTTIManager.GetRTTIForClass("RBX::HttpRbxApiJob")},
        {"RBX::PhysicsStepJob", RTTIManager.GetRTTIForClass("RBX::PhysicsStepJob")}
    };

    constexpr ptrdiff_t stepOffset = offsetof(RobloxJobVFTable, step) / 8;
    for (const auto& [name, rtti]: rttiMap) {
        LUGO_ASSERT(rtti != nullptr, std::format("Could NOT find RTTI for Roblox job {}", name).c_str());

        auto* vft = reinterpret_cast<RobloxJobVFTable*>(rtti->pVirtualFunctionTable);

        this->vtableNameMapping.emplace(vft, name);
        RTTIManager.HookVirtualFunction(name, stepOffset, RBXHooks::GenericJobStep);
    }

    LuGoLog("Hooking complete! Scheduler initialised!", IO::OutputType::Info);
}

void Scheduler::OnRobloxJobStepped(void** job, const RBXJobType jobType, RBX::TaskScheduler::Job::Stats* metrics) {

}
