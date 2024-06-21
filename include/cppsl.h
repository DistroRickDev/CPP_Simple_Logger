/*    Copyright (c) 2024, DistroRickDev
 *    All rights reserved
 *
 *    Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license.
 */

#include <fmt/format.h>
#include <string>

#if !defined(HEADER_CPPSL_H)
#define HEADER_CPPSL_H

namespace cppsl {
    enum class eLogLevel {
        DEBUG,
        ERROR,
        INFO,
        WARNING
    };

#if  defined(LOG_TO_PERSISTENCE)
    void init_logger(std::string logger_file_path);
#endif // LOG_TO_PERSISTENCE

    void init_logger();
    void _log(eLogLevel const& logLevel, std::string const &message);
} // namespace cppsl

#if !defined(NDEBUG)
#define LOG_DEBUG(...) \
    cppsl::_log(cppsl::eLogLevel::DEBUG, fmt::format(__VA_ARGS__));
#else
#define LOG_DEBUG(...)
#endif  // NDEBUG

#define LOG_ERROR(...) \
    cppsl::_log(cppsl::eLogLevel::ERROR, fmt::format(__VA_ARGS__));

#define LOG_INFO(...) \
    cppsl::_log(cppsl::eLogLevel::INFO, fmt::format(__VA_ARGS__));

#define LOG_WARN(...) \
    cppsl::_log(cppsl::eLogLevel::WARNING, fmt::format(__VA_ARGS__));

#endif  // HEADER_CPPSL_H
