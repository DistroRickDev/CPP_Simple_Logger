add_library(${CMAKE_PROJECT_NAME} SHARED ${CMAKE_PROJECT_NAME}.cpp)

if(${LOG_TO_PERSISTENCE})
    message(STATUS "Log to persistence enabled")
    add_compile_definitions(LOG_TO_PERSISTENCE)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} INTERFACE fmt)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)