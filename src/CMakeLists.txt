add_library(${CMAKE_PROJECT_NAME} SHARED cppsl.cpp)

if(${LOG_TO_PERSITANCY})
    message(STATUS "Log to persistancy enabled")
    add_compile_definitions(LOG_TO_PERSITANCY)
endif()