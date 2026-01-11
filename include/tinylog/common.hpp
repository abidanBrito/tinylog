// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string_view>

namespace tinylog
{

    enum class LogLevel : std::uint8_t
    {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        FATAL = 4,
    };

    constexpr auto to_string(LogLevel log_level) noexcept -> std::string_view
    {
        switch (log_level)
        {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::FATAL:
            return "FATAL";
        }

        return "UNKNOWN";
    }

} // namespace tinylog
