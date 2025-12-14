/*
This header file was created by
12345koip for the LuGo executor
on 13/12/2025. See LICENSE and README
for details.
*/

#include "Logger.hpp"
#include <print>
#include <map>

using namespace LuGo;

static constexpr const char* OutputTypeToString(const IO::OutputType outputType) {
    switch (outputType) {
        case IO::OutputType::Error:
            return "ERROR";

        case IO::OutputType::Info:
            return "INFO";

        case IO::OutputType::Warning:
            return "WARNING";

        default:
            return "OTHER";
    }
}

void IO::Logger::Log(const std::string_view message, const char* function, const OutputType outputType) const {
    switch (outputType) {
        case OutputType::Error:
            std::println("\x1b[38;2;255;0;0m[ERROR] -- {} -- {}\x1b[0m", message, function);
            break;

        case OutputType::Warning:
            std::println("\x1b[38;2;255;255;0m[WARNING] -- {} -- {}\x1b[0m", message, function);
            break;

        case OutputType::Info:
            std::println("\x1b[38;2;0;170;255m[INFO] -- {} -- {}\x1b[0m", message, function);
            break;

        default:
            std::println("{} -- {}", message, function);
    }
}