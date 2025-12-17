cmake_minimum_required(VERSION 4.2)
project(LuGo_v2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")

#DLL bits.
add_library(LuGo_Internal SHARED
        src/Internal/Main.cpp
        src/Internal/IO/Logger.cpp
        src/Internal/Analysis/Dissassembler/Dissassembler.hpp
        src/Internal/Analysis/Dissassembler/AsmOperand.hpp
        src/Internal/Analysis/Dissassembler/AsmInstruction.hpp
        src/Internal/Analysis/Dissassembler/AsmInstructionList.hpp
        src/Internal/Common/Attributes.hpp
        src/Internal/Analysis/Dissassembler/AsmInstructionList.cpp
        src/Internal/Analysis/Dissassembler/Dissassembler.cpp
        src/Internal/Analysis/RTTI/RTTIManager.hpp
        src/Internal/Analysis/Offsets/PointerObfuscation.hpp
        src/Internal/Analysis/Offsets/OffsetManager.hpp
        src/Internal/Analysis/Offsets/Scanners/Scanners.hpp
        src/Internal/Analysis/Offsets/Scanners/Scanners.cpp
        src/Internal/Execution/Scheduling/Scheduler.hpp
        src/Internal/Execution/RBXHooks/RBXHooks.hpp
        src/Internal/Execution/RBXHooks/RBXHooks.cpp
        src/Internal/RBX/TaskScheduler.hpp
        src/Internal/Execution/Scheduling/Scheduler.cpp
        src/Internal/Execution/Scheduling/RobloxJob.hpp
)

target_include_directories(LuGo_Internal PUBLIC
        Dependencies/Internal
        src/Internal
        src/
)

set_target_properties(LuGo_Internal PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        OUTPUT_NAME "LuGo.Internal"
)

target_compile_definitions(LuGo_Internal PRIVATE
        $<$<CONFIG:Debug>:DEBUG_BUILD>
)

add_subdirectory(Dependencies/Internal/Capstone)
add_subdirectory(Dependencies/Internal/LibHat)
target_link_libraries(LuGo_Internal PRIVATE capstone)
target_link_libraries(LuGo_Internal PRIVATE libhat)


#UI bits.
#will be done later ok ty