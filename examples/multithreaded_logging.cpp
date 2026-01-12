// Copyright (c) 2026 Abidán Brito
// SPDX-License-Identifier: MIT

#include <tinylog/sync_logger.hpp>

#include <thread>
#include <vector>

auto main() -> int
{
    tinylog::SyncLogger logger("workers.log");

    // Spawn 5 threads, each logging 10 messages
    std::vector<std::thread> workers;
    workers.reserve(5);

    for (int t{0}; t < 5; ++t)
    {
        workers.emplace_back(
            [&logger, t]()
            {
                for (int i{0}; i < 10; ++i)
                {
                    logger.info("Thread {} processing task {}", t, i);
                }
            });
    }

    // Wait for threads to finish
    for (auto& worker : workers)
    {
        worker.join();
    }

    logger.info("All threads completed");

    return 0;
}
