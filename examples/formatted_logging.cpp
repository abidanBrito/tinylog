// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#include <tinylog/sync_logger.hpp>

auto main() -> int
{
    tinylog::SyncLogger logger;

    // Format strings with {} placeholders
    logger.info("Server listening on port {}", 8080);
    logger.info("User '{}' connected from {}", "bob", "192.168.1.100");
    logger.warn("Memory usage: {}%", 90);

    int processed{150};
    int total{200};
    logger.info("Processed {} of {} items ({}% complete)", processed, total,
                (processed * 100) / total);

    return 0;
}
