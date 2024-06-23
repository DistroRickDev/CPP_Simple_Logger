find_package(GTest REQUIRED)

enable_testing()

set(UNIT_TEST_NAME cppsl_ut)

add_executable(
        ${UNIT_TEST_NAME}
        ${UNIT_TEST_NAME}.cpp
)
target_link_libraries(
        ${UNIT_TEST_NAME}
        GTest::gtest_main
        cppsl
)

if(${LOG_TO_PERSISTENCE})
    add_compile_definitions(LOG_TO_PERSISTENCE)
endif()

link_directories(${CMAKE_BINARY_DIR}/src)
target_include_directories(${UNIT_TEST_NAME} PRIVATE ${_CPPSL_INCLUDE_DIR})

include(GoogleTest)
gtest_discover_tests(${UNIT_TEST_NAME})