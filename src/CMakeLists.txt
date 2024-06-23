add_library(cppsl SHARED cppsl.cpp)

if(${LOG_TO_PERSISTENCE})
    message(STATUS "Log to persistence enabled")
    add_compile_definitions(LOG_TO_PERSISTENCE)
endif()

target_include_directories(cppsl PRIVATE ${_CPPSL_INCLUDE_DIR})