// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#pragma once

#include <chrono>
#include <cstdint>
#include <string_view>

namespace tinylog
{

    enum class LogLevel : std::uint8_t
    {
        TRACE = 0,
        DEBUG = 1,
        INFO  = 2,
        WARN  = 3,
        ERROR = 4,
        FATAL = 5,
    };

    constexpr auto to_string(LogLevel level) noexcept -> std::string_view
    {
        switch (level)
        {
        case LogLevel::TRACE:
            return "TRACE";
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

    inline auto timestamp_now() -> std::string
    {
        auto current = std::chrono::system_clock::now();
        auto time    = std::chrono::system_clock::to_time_t(current);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(current.time_since_epoch())
                  % 1000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0')
            << std::setw(3) << ms.count();

        return oss.str();
    }

} // namespace tinylog
