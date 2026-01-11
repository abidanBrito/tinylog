// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#pragma once

#include "common.hpp"

#include <format>
#include <iostream>
#include <fstream>
#include <memory>
#include <mutex>
#include <thread>

namespace tinylog
{

    class SyncLogger
    {
    public:
        explicit SyncLogger(LogLevel level = LogLevel::INFO)
            : level_{level},
              out_{&std::cout},
              owns_stream_{false}
        {
        }

        explicit SyncLogger(const std::string& filepath, LogLevel level = LogLevel::INFO)
            : level_{level},
              file_{std::make_unique<std::ofstream>(filepath, std::ios::app)},
              out_{file_.get()},
              owns_stream_{true}

        {
        }

        ~SyncLogger() = default;

        SyncLogger(const SyncLogger&) = delete;
        auto operator=(const SyncLogger&) -> SyncLogger& = delete;

        SyncLogger(SyncLogger&&) = delete;
        auto operator=(SyncLogger&&) -> SyncLogger& = delete;

        auto set_level(LogLevel level) -> void
        {
            std::lock_guard<std::mutex> lock(mutex_);
            level_ = level;
        }

        template <typename... Args>
        auto log(LogLevel level, const std::string& msg, Args&&... args) -> void
        {
            if (level < level_)
            {
                return;
            }

            std::lock_guard<std::mutex> lock(mutex_);
            *out_ << "[" << "Timestamp" << "]"
                  << " [" << to_string(level) << "]"
                  << " " << std::format(msg, std::forward<Args>(args)...) << "\n";

            if (owns_stream_)
            {
                out_->flush();
            }
        }

        template <typename... Args>
        auto debug(const std::string& msg, Args&&... args) -> void
        {
            log(LogLevel::DEBUG, msg, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto info(const std::string& msg, Args&&... args) -> void
        {
            log(LogLevel::INFO, msg, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto warn(const std::string& msg, Args&&... args) -> void
        {
            log(LogLevel::WARN, msg, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto error(const std::string& msg, Args&&... args) -> void
        {
            log(LogLevel::ERROR, msg, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto fatal(const std::string& msg, Args&&... args) -> void
        {
            log(LogLevel::FATAL, msg, std::forward<Args>(args)...);
        }

    private:
        LogLevel level_;
        std::unique_ptr<std::ofstream> file_;
        std::ostream* out_;
        std::mutex mutex_;
        bool owns_stream_;
    };

} // namespace tinylog
