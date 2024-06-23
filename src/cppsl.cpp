/*    Copyright (c) 2024, DistroRickDev
 *    All rights reserved
 *
 *    Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license.
 */

#include "cppsl.h"

#include <ctime>
#if defined(LOG_TO_PERSISTENCE)
#include <fstream>
#endif // LOG_TO_PERSISTENCE
#include <fmt/format.h>
#include <iomanip>
#include <iostream>

auto raw_time{std::time(nullptr)};

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__) // only show filename and not it's path (less clutter)
#define LOG_PREFIX std::put_time(std::localtime(&raw_time), "%c ") << __FILENAME__ << "(" << __FUNCTION__ << ":" << __LINE__ << ") "

namespace
{
    std::string log_level_to_string(cppsl::eLogLevel const& logLevel)
    {
        switch (logLevel) {
            case cppsl::eLogLevel::DEBUG:
                return "[DEBUG]: ";
            case cppsl::eLogLevel::ERROR:
                return "[ERROR]: ";
            case cppsl::eLogLevel::INFO:
                return "[INFO]: ";
            case cppsl::eLogLevel::WARNING:
                [[fallthrough]];
            default:
                return "[WARNING]: ";
        }
    }

    struct logger
    {
#if defined(LOG_TO_PERSISTENCE)
        explicit logger(std::string logger_file_path)
            : _logger_file(std::ofstream(std::move(logger_file_path)))
        {
            if (!_logger_file.good())
            {
                throw std::runtime_error("Failed to init log file " + logger_file_path);
            }
        }
#endif // LOG_TO_PERSISTENCE

        void log_message(std::string const &log_level, std::string const& formated_message)
        {
#if defined(LOG_TO_PERSISTENCE)
            _logger_file << LOG_PREFIX << log_level << formated_message << std::endl;
#else
            std::cout << LOG_PREFIX << log_level << formated_message << std::endl;
#endif // LOG_TO_PERSISTENCE
        }
#if defined(LOG_TO_PERSISTENCE)
        std::ofstream _logger_file;
#endif // LOG_TO_PERSISTENCE
    };

    std::unique_ptr<logger> _logger;
} // namespace

#if defined(LOG_TO_PERSISTENCE)
void cppsl::init_logger(std::string logger_file_path = "/tmp/out.log")
#else
void cppsl::init_logger()
#endif // LOG_TO_PERSISTENCE
{
    if (!_logger)
    {
#if defined(LOG_TO_PERSISTENCE)
        _logger = std::make_unique<logger>(std::move(logger_file_path));
#else
        _logger = std::make_unique<logger>();
#endif // LOG_TO_PERSISTENCE
    }
    LOG_DEBUG("Logger initialized successfully: {}", 1);
}

void cppsl::_log(cppsl::eLogLevel const& logLevel, std::string const &message)
{
    if (!_logger)
    {
        throw std::runtime_error("Logger not initialized");
    }
//    auto const formated_message{fmt::format(message, fmt::make_format_args(args...))};
    _logger->log_message(log_level_to_string(logLevel), message);
}