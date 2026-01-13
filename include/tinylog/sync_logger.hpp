// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#pragma once

#include "color.hpp"
#include "common.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>

namespace tinylog
{
    class SyncLogger
    {
    public:
        explicit SyncLogger(LogLevel level = LogLevel::INFO, ColorMode color_mode = ColorMode::AUTO)
            : level_{level},
              out_{&std::cout},
              owns_stream_{false},
              use_colors_{should_use_colors(color_mode, false)}
        {
        }

        explicit SyncLogger(const std::string& filepath, LogLevel level = LogLevel::INFO)
            : level_{level},
              file_{std::make_unique<std::ofstream>(filepath, std::ios::app)},
              out_{file_.get()},
              owns_stream_{true},
              use_colors_{false}
        {
            if (!file_->is_open())
            {
                throw std::runtime_error("Failed to open log file: " + filepath);
            }
        }

        ~SyncLogger() = default;

        SyncLogger(const SyncLogger&)                    = delete;
        auto operator=(const SyncLogger&) -> SyncLogger& = delete;

        SyncLogger(SyncLogger&&)                    = delete;
        auto operator=(SyncLogger&&) -> SyncLogger& = delete;

        auto set_level(LogLevel level) -> void
        {
            std::lock_guard<std::mutex> lock(mutex_);
            level_ = level;
        }

        auto set_color_mode(ColorMode mode) -> void
        {
            std::lock_guard<std::mutex> lock(mutex_);
            use_colors_ = should_use_colors(mode, owns_stream_);
        }

        template <typename... Args>
        auto log(LogLevel level, std::format_string<Args...> fmt, Args&&... args) -> void
        {
            if (level < level_)
            {
                return;
            }

            std::lock_guard<std::mutex> lock(mutex_);

            *out_ << "[" << timestamp_now() << "]";

            if (use_colors_)
            {
                *out_ << " " << detail::get_level_color_code(level) << "[" << to_string(level)
                      << "]" << detail::get_reset_code();
            }
            else
            {
                *out_ << " [" << to_string(level) << "]";
            }

            *out_ << " " << std::format(fmt, std::forward<Args>(args)...) << "\n";

            if (owns_stream_)
            {
                out_->flush();
            }
        }

        template <typename... Args>
        auto debug(std::format_string<Args...> fmt, Args&&... args) -> void
        {
            log(LogLevel::DEBUG, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto info(std::format_string<Args...> fmt, Args&&... args) -> void
        {
            log(LogLevel::INFO, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto warn(std::format_string<Args...> fmt, Args&&... args) -> void
        {
            log(LogLevel::WARN, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto error(std::format_string<Args...> fmt, Args&&... args) -> void
        {
            log(LogLevel::ERROR, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto fatal(std::format_string<Args...> fmt, Args&&... args) -> void
        {
            log(LogLevel::FATAL, fmt, std::forward<Args>(args)...);
        }

    private:
        LogLevel                       level_;
        std::unique_ptr<std::ofstream> file_;
        std::ostream*                  out_;
        std::mutex                     mutex_;
        bool                           owns_stream_;
        bool                           use_colors_;

        [[nodiscard]] static auto should_use_colors(ColorMode mode, bool is_file) -> bool
        {
            if (is_file)
            {
                return false;
            }

            switch (mode)
            {
            case ColorMode::ALWAYS:
                return true;
            case ColorMode::NEVER:
                return false;
            case ColorMode::AUTO:
                return detail::is_terminal_color_supported();
            }

            return false;
        }
    };
} // namespace tinylog
