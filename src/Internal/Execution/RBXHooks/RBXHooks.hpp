/*
This file was created by
12345koip for the LuGo executor
on 17/12/2025. See LICENSE and README
for details.
*/

#pragma once
#include "RBX/TaskScheduler.hpp"

//NOTE: contains hooks around raw Roblox functions, not related to Luau hooks.
namespace LuGo::Execution::RBXHooks {
    bool GenericJobStep(void** self, RBX::TaskScheduler::Job::Stats* metrics);
};