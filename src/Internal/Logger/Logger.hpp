/*
This header file was created by
12345koip for the LuGo executor
on 13/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include <windows.h>
#include <cstdint>

namespace LuGo {
    namespace IO {

        enum class OutputType: uint8_t {
            Normal,
            Warning,
            Error,
            Info
        };

        class Logger final {
            private:
                Logger() {
                    AllocConsole();
                }
        };
    }
}