// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#pragma once

#include "common.hpp"

#include <cstdint>
#include <string_view>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdlib>
    #include <unistd.h>
#endif

namespace tinylog
{
    enum class ColorMode : std::uint8_t
    {
        AUTO,
        ALWAYS,
        NEVER,
    };

    namespace detail
    {
        constexpr std::string_view RESET = "\033[0m";

        // Foreground colors
        constexpr std::string_view BLACK   = "\033[30m";
        constexpr std::string_view RED     = "\033[31m";
        constexpr std::string_view GREEN   = "\033[32m";
        constexpr std::string_view YELLOW  = "\033[33m";
        constexpr std::string_view BLUE    = "\033[34m";
        constexpr std::string_view MAGENTA = "\033[35m";
        constexpr std::string_view CYAN    = "\033[36m";
        constexpr std::string_view WHITE   = "\033[37m";

        constexpr std::string_view BRIGHT_BLACK   = "\033[90m";
        constexpr std::string_view BRIGHT_RED     = "\033[91m";
        constexpr std::string_view BRIGHT_GREEN   = "\033[92m";
        constexpr std::string_view BRIGHT_YELLOW  = "\033[93m";
        constexpr std::string_view BRIGHT_BLUE    = "\033[94m";
        constexpr std::string_view BRIGHT_MAGENTA = "\033[95m";
        constexpr std::string_view BRIGHT_CYAN    = "\033[96m";
        constexpr std::string_view BRIGHT_WHITE   = "\033[97m";

        // Styles
        constexpr std::string_view BOLD = "\033[1m";
        constexpr std::string_view DIM  = "\033[2m";

        constexpr auto get_reset_code() -> std::string_view
        {
            return RESET;
        }

        constexpr auto get_level_color_code(LogLevel level) -> std::string_view
        {
            switch (level)
            {
            case LogLevel::TRACE: return BRIGHT_BLACK;
            case LogLevel::DEBUG: return CYAN;
            case LogLevel::INFO:  return GREEN;
            case LogLevel::WARN:  return YELLOW;
            case LogLevel::ERROR: return RED;
            case LogLevel::FATAL: return BRIGHT_RED;
            }

            return {};
        }

        inline auto is_terminal_color_supported() -> bool
        {
#ifdef _WIN32
            // NOTE(abi): windows 10+ supports ANSI colors via VT100 emulation,
            //            so we need to enable VT processing.
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hOut == INVALID_HANDLE_VALUE)
            {
                return false;
            }

            DWORD dwMode = 0;
            if (!GetConsoleMode(hOut, &dwMode))
            {
                return false;
            }

            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            return SetConsoleMode(hOut, dwMode) != 0;
#else
            if (!static_cast<bool>(isatty(fileno(stdout))))
            {
                return false;
            }

            const char* term = std::getenv("TERM");
            if (term == nullptr)
            {
                return false;
            }

            // Check if TERM suggests color support
            std::string_view term_str(term);
            return term_str != "dumb";
#endif
        }
    } // namespace detail
} // namespace tinylog
