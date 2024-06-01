/*    Copyright (c) 2024, DistroRickDev
 *    All rights reserved
 *
 *    Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license.
 */

#include "cppsl.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <fmt/format.h>
#include <memory>

auto raw_time{std::time(nullptr)};

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__) // only show filename and not it's path (less clutter)
#define LOG_PREFIX std::put_time(std::localtime(&raw_time), "%c ") << __FILENAME__ << "(" << __FUNCTION__ << ":" << __LINE__ << ") "

namespace
{
    struct logger
    {
#if defined(LOG_TO_PERSITANCY)
        explicit logger(std::string logger_file_path)
            : _logger_file(std::ofstream(std::move(logger_file_path)))
        {
            if (!_logger_file.good())
            {
                throw std::runtime_error("Failed to init log file " + logger_file_path);
            }
        }
#endif // LOG_TO_PERSITANCY
        void log_message(std::string msg)
        {
#if defined(LOG_TO_PERSITANCY)
            _logger_file << LOG_PREFIX << msg << std::endl;
#else
            std::cout << LOG_PREFIX << msg << std::endl;
#endif // LOG_TO_PERSITANCY
        }
#if defined(LOG_TO_PERSITANCY)
        std::ofstream _logger_file;
#endif // LOG_TO_PERSITANCY
    };

    static std::unique_ptr<logger> _logger;
} // namespace

#if defined(LOG_TO_PERSITANCY)
void cppsl::init_logger(std::string logger_file_path = "/tmp/out.log")
#else
void cppsl::init_logger()
#endif // LOG_TO_PERSITANCY
{
    if (!_logger)
    {
#if defined(LOG_TO_PERSITANCY)
        _logger = std::make_unique<logger>(std::move(logger_file_path));
#else
        _logger = std::make_unique<logger>();
#endif // LOG_TO_PERSITANCY
    }
    LOG_DEBUG("Logger initialized successfully");
}

void cppsl::_log(std::string msg)
{
    if (!_logger)
    {
        throw std::runtime_error("Logger not initialized");
    }
    _logger->log_message(std::move(msg));
}