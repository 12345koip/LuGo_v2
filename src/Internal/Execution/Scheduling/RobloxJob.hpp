/*
This file was created by
12345koip for the LuGo executor
on 17/12/2025. See LICENSE and README
for details.
*/

#pragma once
#include <cstdint>
#include <string_view>

namespace LuGo::Execution::Scheduling {
    enum class RBXJobType: uint8_t {
        Studio_DebuggerConnectionJob,
        ModelMeshJob,
        ScriptContextFacets_GcJob,
        ScriptContextFacets_WaitingHybridScriptsJob,
        HeartbeatTask,
        PhysicsJob,
        NavigationService_PathUpdateJob,
        NagivationService_NavigationJob,
        GenericDataModelJob,
        HttpRbxApiJob,
        PhysicsStepJob
    };


    constexpr const char* RBXJobTypeToString(const RBXJobType type) {
        switch (type) {
            case RBXJobType::Studio_DebuggerConnectionJob:                return "RBX::Studio::DebuggerConnectionJob";
            case RBXJobType::ModelMeshJob:                                return "RBX::ModelMeshJob";
            case RBXJobType::ScriptContextFacets_GcJob:                   return "RBX::ScriptContextFacets::GcJob";
            case RBXJobType::ScriptContextFacets_WaitingHybridScriptsJob: return "RBX::ScriptContextFacets::WaitingHybridScriptsJob";
            case RBXJobType::HeartbeatTask:                               return "RBX::HeartbeatTask";
            case RBXJobType::PhysicsJob:                                  return "RBX::PhysicsJob";
            case RBXJobType::NavigationService_PathUpdateJob:             return "RBX::NavigationService::PathUpdateJob";
            case RBXJobType::NagivationService_NavigationJob:             return "RBX::NagivationService::NavigationJob";
            case RBXJobType::GenericDataModelJob:                         return "RBX::GenericDataModelJob";
            case RBXJobType::HttpRbxApiJob:                               return "RBX::HttpRbxApiJob";
            case RBXJobType::PhysicsStepJob:                              return "RBX::PhysicsStepJob";
            default:                                                      return "UNKNOWN";
        }
    }

}