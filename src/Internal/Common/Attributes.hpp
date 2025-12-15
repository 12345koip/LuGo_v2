/*
This file was created by
12345koip for the LuGo executor
on 14/12/2025. See LICENSE and README
for details.
*/

#pragma once

#include <source_location>
#include <windows.h>
#include <cstdio>
#include <cstdlib>

#define L_FORCEINLINE __forceinline
#define L_NOINLINE __declspec(noinline)
#define L_ALIGN(N) __declspec(align(N))
#define L_NORETURN __declspec(noreturn) void
#define L_NODISCARD [[nodiscard]]


//NOTE: assertions will only ever be used after the initialisation of the logger, so we can safely write output.
static L_NORETURN _lugo_assertion_fail_handler(const char* expression, const char* message, const std::source_location location) {
    std::fprintf(stderr,
        "\n\n--------------------\n"
        "[[ASSERTION FAILED]]\n"
        "Expression: %s\n"
        "Function: %s\n"
        "Line: %u\n"
        "Message: %s\n",

        expression, location.function_name(), location.line(), message
    );

    #ifdef DEBUG_BUILD
    if (IsDebuggerPresent())
        __debugbreak();
    #endif

    MessageBoxA(nullptr, "Assertion failed! Check output!", "Assertion failed", 0);

    std::abort();
}

#define LUGO_ASSERT(expr, msg) {if (!(expr)) _lugo_assertion_fail_handler(#expr, msg, std::source_location::current());}