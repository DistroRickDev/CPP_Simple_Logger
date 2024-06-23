/*    Copyright (c) 2024, DistroRickDev
 *    All rights reserved
 *
 *    Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license.
 */

#include "cppsl.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


namespace {
#if defined(LOG_TO_PERSISTENCE)

#endif // LOG_TO_PERSISTENCE
}

TEST(CPPSL, logger_throws_when_unitialized)
{
    ASSERT_ANY_THROW(LOG_INFO("Hello {}", "fail"));
}

#if defined(LOG_TO_PERSISTENCE)
TEST(CPPSL, test_log_debug_happy_path)
{

}

TEST(CPPSL, test_log_error_happy_path)
{

}

TEST(CPPSL, test_log_info_happy_path)
{

}

TEST(CPPSL, test_log_wanr_happy_path)
{

}

#else
#if !defined(NDEBUG)
TEST(CPPSL, test_log_debug_happy_path)
{
    cppsl::init_logger();
    testing::internal::CaptureStdout();
    LOG_DEBUG("Hello {}", "World");
    auto result {testing::internal::GetCapturedStdout()};
    EXPECT_THAT(result, testing::HasSubstr("DEBUG"));
    EXPECT_THAT(result, testing::HasSubstr("Hello World"));
}
#endif // !NDEBUG

TEST(CPPSL, test_log_error_happy_path)
{
    cppsl::init_logger();
    testing::internal::CaptureStdout();
    LOG_ERROR("Hello {}", "World");
    auto result {testing::internal::GetCapturedStdout()};
    EXPECT_THAT(result, testing::HasSubstr("ERROR"));
    EXPECT_THAT(result, testing::HasSubstr("Hello World"));
}

TEST(CPPSL, test_log_info_happy_path)
{
    cppsl::init_logger();
    testing::internal::CaptureStdout();
    LOG_INFO("Hello {}", "World");
    auto result {testing::internal::GetCapturedStdout()};
    EXPECT_THAT(result, testing::HasSubstr("INFO"));
    EXPECT_THAT(result, testing::HasSubstr("Hello World"));
}

TEST(CPPSL, test_log_warn_happy_path)
{
    cppsl::init_logger();
    testing::internal::CaptureStdout();
    LOG_WARN("Hello {}", "World");
    auto result {testing::internal::GetCapturedStdout()};
    EXPECT_THAT(result, testing::HasSubstr("WARN"));
    EXPECT_THAT(result, testing::HasSubstr("Hello World"));
}

#endif // LOG_TO_PERSISTENCE

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}