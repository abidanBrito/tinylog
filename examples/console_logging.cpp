// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#include <tinylog/sync_logger.hpp>

auto main() -> int
{
    tinylog::SyncLogger logger(tinylog::LogLevel::TRACE);

    logger.trace("Application starting...");
    logger.debug("Loading configuration file from config.yaml...");
    logger.info("Server listening on port 8080");
    logger.warn("Cache is 80% full");
    logger.error("Failed to connect to database");
    logger.fatal("Out of memory!");

    return 0;
}
