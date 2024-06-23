/*    Copyright (c) 2024, DistroRickDev
 *    All rights reserved
 *
 *    Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license.
 */

#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>

#if !defined(HEADER_CPPSL_H)
#define HEADER_CPPSL_H

namespace cppsl {
    enum class eLogLevel {
        DEBUG,
        ERROR,
        INFO,
        WARNING
    };

auto format_message(std::string const& fmt, auto&& ...s) -> std::string
{
    std::vector<std::string> arguments;
    for(const auto &p : {s...}) {
        if(std::is_convertible<decltype(p), std::string>::value)
        {
            throw std::runtime_error("Invalid type conversion");
        }
        std::stringstream tmp;
        tmp << p;
        arguments.push_back(tmp.str());
    }
    if(fmt.find("{}") != std::string::npos)
    {
        if(arguments.empty())
        {
            throw std::runtime_error("Invalid number of format arguments");
        }
        auto formated_string {fmt};
        auto current_arg{std::begin(arguments)};
        auto current {formated_string.find_first_of("{}")};
        while(current != std::string::npos)
        {
            if(std::end(arguments) == current_arg)
            {
                throw std::runtime_error("Invalid number of format arguments");
            }
            formated_string.replace(current, current+1, *current_arg);
            current_arg++;
            current = formated_string.find_first_of("{}");
        }
        return formated_string;
    }
    return fmt;
}

#if  defined(LOG_TO_PERSISTENCE)
    void init_logger(std::string const& logger_file_path = "/tmp/cppsl.log");
#endif // LOG_TO_PERSISTENCE

    void init_logger();
    void _log(eLogLevel const& logLevel, std::string const &message);
} // namespace cppsl

#if !defined(NDEBUG)
#define LOG_DEBUG(...) \
    cppsl::_log(cppsl::eLogLevel::DEBUG, cppsl::format_message(__VA_ARGS__));
#else
#define LOG_DEBUG(...)
#endif  // NDEBUG

#define LOG_ERROR(...) \
    cppsl::_log(cppsl::eLogLevel::ERROR, cppsl::format_message(__VA_ARGS__));

#define LOG_INFO(...) \
    cppsl::_log(cppsl::eLogLevel::INFO, cppsl::format_message(__VA_ARGS__));

#define LOG_WARN(...) \
    cppsl::_log(cppsl::eLogLevel::WARNING, cppsl::format_message(__VA_ARGS__));

#endif  // HEADER_CPPSL_H
