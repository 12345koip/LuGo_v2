/*
This file was created by
12345koip for the LuGo executor
on 13/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include <windows.h>
#include <cstdint>
#include <string>

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
                    SetConsoleTitleA("LuGo v2");

                    //allow text colouring in the console window.
                    freopen("CONOUT$", "w", stdout);
                    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
                    DWORD mode = 0;
                    GetConsoleMode(hOut, &mode);
                    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                    SetConsoleMode(hOut, mode);

                    //reroute standard output to the new console.
                    FILE* fp;
                    freopen_s(&fp, "CONOUT$", "w", stdout);
                    freopen_s(&fp, "CONOUT$", "w", stderr);
                    freopen_s(&fp, "CONIN$", "r", stdin);
                }

                ~Logger() {
                    FreeConsole();
                }

            public:
                static Logger& GetSingleton() {
                    static Logger singleton;
                    return singleton;
                }

                void Log(const std::string_view message, const char* function, const OutputType outputType = OutputType::Normal) const;
        };

        //logger macro for easy function name in the message.
        #define LuGoLog(message, type) LuGo::IO::Logger::GetSingleton().Log((message), __FUNCTION__, type)
    }
}