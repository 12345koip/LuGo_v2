cmake_minimum_required(VERSION 4.2)
project(LuGo_v2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")


#DLL bits.
add_library(LuGo_Internal SHARED
        src/Internal/Main.cpp
        src/Internal/Logger/Logger.cpp
)

target_include_directories(LuGo_Internal PUBLIC
        Dependencies/Internal
)

set_target_properties(LuGo_Internal PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        OUTPUT_NAME "LuGo.Internal"
)

#UI bits.
#will be done later ok ty