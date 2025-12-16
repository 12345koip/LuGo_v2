/*
This file was created by
12345koip for the LuGo executor
on 16/12/2025. See LICENSE and README
for details.
*/

#include <future>
#include <vector>
#include "Scanners.hpp"

#include "Analysis/Dissassembler/Dissassembler.hpp"
#include "Analysis/Offsets/OffsetManager.hpp"
#include "Common/Attributes.hpp"
#include "Logger/Logger.hpp"

using namespace LuGo::Analysis::Offsets;
using namespace LuGo::IO;

static std::map<RawPointerOffsetRef, hat::scan_result> ScanManyAOBsInSection(const std::map<RawPointerOffsetRef, hat::signature>& signatureMap, const char* section = ".text") {
    std::vector<std::future<std::pair<RawPointerOffsetRef, hat::scan_result>>> futures {};
    futures.reserve(signatureMap.size());

    //we will launch each scan asynchronously.
    for (const auto& signaturePair: signatureMap) {
        futures.emplace_back(
            std::async(std::launch::async, [&signaturePair, section]() -> std::pair<RawPointerOffsetRef, hat::scan_result> {
                const RawPointerOffsetRef& signature = signaturePair.first;
                const hat::scan_result match = hat::find_pattern(signaturePair.second, section);

                return std::make_pair(signature, match);
            })
        );
    }

    //wait for each scan and gather results.
    std::map<RawPointerOffsetRef, hat::scan_result> results {};
    for (auto& future: futures) {
        future.wait();
        results.emplace(future.get());
    }

    return results;
}



void Scanners::Luau::ScanGlobals() {
    auto& OffsetManager = OffsetManager::GetSingleton();
    LuGoLog("Scanning for Luau globals...", OutputType::Info);

    const std::map<RawPointerOffsetRef, hat::signature> signatureMap = {
        {RawPointerOffsetRef::luaC_fullgc, hat::parse_signature("48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 83 EC ?? 48 8B 59 ?? 48 8B F9 0F B6 4B ?? 84 C9 75 ?? E8 ?? ?? ?? ?? 0F B6 4B ?? F2 0F 11 83 ?? ?? ?? ?? F2 0F 5C 83 ?? ?? ?? ?? F2 0F 11 83 ?? ?? ?? ?? 8D 41 ?? 33 ED 3C ?? 76 ?? 84 C9 74 ?? EB ?? 48 8B 83 ?? ?? ?? ?? 48 89 83 ?? ?? ?? ?? 48 89 6B ?? 48 89 6B ?? 48 89 6B ?? C6 43 ?? ?? 48 C7 C2 ?? ?? ?? ?? 48 8B CF E8 ?? ?? ?? ?? 40 38 6B ?? 75 ?? 48 8B 43 ?? 48 8D 4B ?? ?? ?? ?? ??").value()},
        {RawPointerOffsetRef::luaC_step, hat::parse_signature("48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 41 56 41 57 48 83 ec 30 48 8b 59 ?? b8 1f 85 eb 51 0f b6 f2 0f 29 74 24 20 4c 8b f1 44 8b 43 ?? 44 0f af 43 ?? 48 8b 6b ?? 48 2b 6b ?? 41 f7 e8 8b fa c1 ff 05 8b c7 c1 e8 1f 03 f8 48 8b 83 ?? ?? ?? ?? 48 85 c0 74 04 33 d2 ff d0 0f b6 43 ?? 84 c0 75 32 e8 ?? ?? ?? ?? 0f b6 43 ?? f2 0f 11 83 ?? ?? ?? ?? 84 c0 75 1d e8 ?? ?? ?? ?? f2 0f 11 83 ?? ?? ?? ?? f2 0f 5c 83 ?? ?? ?? ??").value()},
        {RawPointerOffsetRef::luaH_new, hat::parse_signature("48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 83 EC ?? 41 8B F0 8B EA 44 0F B6 41 ?? BA ?? ?? ?? ?? 48 8B F9 E8 ?? ?? ?? ?? 4C 8B 4F ?? 48 8B D8 45 0F B6 51 ?? C6 00 ?? 41 80 E2 ?? 44 88 50 ?? 44 0F B6 47 ?? 44 88 40 ??").value()}
    };

    const auto scanResults = ScanManyAOBsInSection(signatureMap, ".text");

    //store each address.
    for (const auto& [ref, result]: scanResults) {
        LUGO_ASSERT(result.has_result(), std::format("Could NOT find Luau C function {}", RawPointerOffsetRefToString(ref)).c_str());

        const auto address = reinterpret_cast<uintptr_t>(result.get());
        LuGoLog(std::format("{} @ {:#x}", RawPointerOffsetRefToString(ref), address), OutputType::Normal);
        OffsetManager.SetPointerOffset(ref, address);
    }

    LuGoLog("Luau global scan finished!", OutputType::Info);
}



void Scanners::RBX::ScanGlobals() {
    auto& OffsetManager = OffsetManager::GetSingleton();
    LuGoLog("Scanning for Roblox globals...", OutputType::Info);

    static std::map<RawPointerOffsetRef, hat::signature> signatureMap = {
        {RawPointerOffsetRef::RBX_ScriptContext_ResumeImpl, hat::parse_signature("48 8B C4 44 89 48 ?? 4C 89 40 ?? 48 89 50 ?? 48 89 48 ?? 53").value()},
        {RawPointerOffsetRef::RBX_Instance_PushInstance, hat::parse_signature("48 89 5C 24 08 57 48 83 EC 20 48 8B FA 48 8B D9 E8 ?? ?? ?? ?? 48 8B CB 84 C0 74 ?? 48 8B D7 48 8B 5C 24 30 48 83 C4 20 5F E9 ?? ?? ?? ?? 48 8B 5C 24 30 48 83 C4 20 5F E9 ?? ?? ?? ?? CC CC CC").value()},
        {RawPointerOffsetRef::RBX_ScriptContext_GetGlobalState, hat::parse_signature("48 89 5c 24 ?? 48 89 74 24 ?? 57 48 83 ec 20 49 8b f8 48 8b f2 48 8b d9 8b 81 ?? ?? ?? ?? 90 83 f8 03 7c 20 48 8d 05 ?? ?? ?? ?? 48 89 44 24 48 48 8b 54 24 48 48 81 ea").value()}
    };

    const auto scanResults = ScanManyAOBsInSection(signatureMap, ".text");

    //store each address.
    for (const auto& [ref, result]: scanResults) {
        LUGO_ASSERT(result.has_result(), std::format("Could NOT find Roblox C function {}", RawPointerOffsetRefToString(ref)).c_str());

        const auto address = reinterpret_cast<uintptr_t>(result.get());
        LuGoLog(std::format("{} @ {:#x}", RawPointerOffsetRefToString(ref), address), OutputType::Normal);
        OffsetManager.SetPointerOffset(ref, address);
    }

    LuGoLog("Roblox global scan finished!", OutputType::Info);
}


void Scanners::RBX::ScanPointerOffsets() {
    auto& OffsetManager = OffsetManager::GetSingleton();
    auto& Dissassembler = Dissassembler::GetSingleton();
    LuGoLog("Scanning for pointer obfuscations...", OutputType::Info);


    { //find the offset which ScriptContext::resumeImpl applies to the offset ScriptContext pointer.
        uintptr_t ScriptContext_resume_start = OffsetManager.GetPointerOffset(RawPointerOffsetRef::RBX_ScriptContext_ResumeImpl);
        uintptr_t dissassembleEndPoint = ScriptContext_resume_start + 0x75;

        const auto possibleInstructions = Dissassembler.Dissassemble(
            reinterpret_cast<uint8_t*>(ScriptContext_resume_start),
            reinterpret_cast<uint8_t*>(dissassembleEndPoint)
        );

        LUGO_ASSERT(possibleInstructions.has_value(), "Could NOT get dissassembly for ScriptContext::resumeImpl");
        const AsmInstructionList& instructionList = *possibleInstructions;

        //the first lea instruction is the calculation of the actual ScriptContext pointer.
        const AsmInstruction* firstLea = instructionList.GetInstructionWhichMatches(X86_INS_LEA);
        const auto ScriptContext_offset = firstLea->detail[1].disp;

        auto obfuscationRep = std::make_shared<ObfuscatedPointer>(PointerObfuscationType::Add, ScriptContext_offset);
        OffsetManager.SetPointerObfuscation(ObfuscatedPointerRef::ScriptContext, obfuscationRep);

        LuGoLog(std::format("ScriptContext::resumeImpl uses pointer offset by {:#x}", ScriptContext_offset), OutputType::Normal);
    }



    LuGoLog("Pointer obfuscation scan complete!", OutputType::Info);
}
