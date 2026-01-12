// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#include <tinylog/sync_logger.hpp>

auto main() -> int
{
    // Start with INFO level (default)
    // NOTE(abi): you may explicitly set the log level during construction.
    tinylog::SyncLogger logger;

    logger.info("Application started in INFO level");
    logger.debug("Debug message - won't show");

    // Change to DEBUG level
    logger.set_level(tinylog::LogLevel::DEBUG);

    logger.info("Switched to DEBUG level");
    logger.debug("Debug message - now visible!");

    // Change to WARN level
    logger.set_level(tinylog::LogLevel::WARN);

    logger.info("Info message - won't show");
    logger.debug("Debug message - won't show");
    logger.warn("Warning message - this shows!");
    logger.error("Error message - this shows too!");

    return 0;
}
