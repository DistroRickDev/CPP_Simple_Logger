find_package(GTest REQUIRED)

enable_testing()

set(UNIT_TEST_NAME ${CMAKE_PROJECT_NAME}_ut)

add_executable(
        ${UNIT_TEST_NAME}
        ${UNIT_TEST_NAME}.cpp
)
target_link_libraries(
        ${UNIT_TEST_NAME}
        GTest::gtest_main
        ${CMAKE_PROJECT_NAME}
)
link_directories(${CMAKE_BINARY_DIR}/src)
target_include_directories(${UNIT_TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(${UNIT_TEST_NAME})