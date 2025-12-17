/*
This file was created by
12345koip for the LuGo executor
on 17/12/2025. See LICENSE and README
for details.
*/

#include "RBXHooks.hpp"
#include "Analysis/RTTI/RTTIManager.hpp"
#include "Execution/Scheduling/Scheduler.hpp"

using namespace LuGo::Execution;

bool RBXHooks::GenericJobStep(void** self, RBX::TaskScheduler::Job::Stats* metrics) {
    auto& Scheduler = Scheduling::Scheduler::GetSingleton();
    const auto& RTTIManager = Analysis::RTTI::RTTIManager::GetSingleton();

    //we must retrieve information about the job, and its old vtable state.
    const auto jobVT = *reinterpret_cast<Scheduling::RobloxJobVFTable**>(self);
    const auto jobName = Scheduler.GetJobNameFromVTable(jobVT);

    if (jobName.empty())
        throw std::exception("RBXCRASH: wuh oh");

    //get hook info, signal a step to the LuGo scheduler, then run the original step function.
    const auto hookInformation = RTTIManager.GetVFTHookForClass(jobName);
    Scheduler.OnRobloxJobStepped(self, Scheduler.m_jobEnumLookupMap.at(jobName), metrics);

    const auto oldStep = reinterpret_cast<bool(__fastcall*)(void* job, RBX::TaskScheduler::Job::Stats* stats)>(hookInformation->originalFunction);
    return oldStep(self, metrics);
}
