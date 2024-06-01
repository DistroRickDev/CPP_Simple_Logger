/*    Copyright (c) 2024, DistroRickDev
 *    All rights reserved
 *
 *    Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license.
 */

#pragma once

#include <string>

namespace cppsl
{
#if  defined(LOG_TO_PERSITANCY)
    void init_logger(std::string logger_file_path);
#endif // LOG_TO_PERSITANCY
    void init_logger();
    void _log(std::string msg);
} // namespace cppsl

#if !defined(NDEBUG)
#define LOG_DEBUG(...) \
    _log("[DEBUG]: " + fmt::format(__VA_ARGS__));
#else
#define LOG_DEBUG(...)
#endif  // NDEBUG

#define LOG_ERROR(...) \
    _log("[ERROR]: " + fmt::format(__VA_ARGS__));

#define LOG_INFO(...) \
    _log("[INFO]: " << fmt::format(__VA_ARGS__));

#define LOG_WARN(...) \
    _log("[WARN]: " << fmt::format(__VA_ARGS__));
