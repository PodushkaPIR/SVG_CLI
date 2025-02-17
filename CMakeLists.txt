cmake_minimum_required(VERSION 3.30.1)

project(SVG_CLI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)

find_library(LINENOISE_LIBRARY linenoise PATHS /usr/lib)
find_path(LINENOISE_INCLUDE_DIR linenoise.h PATHS /usr/include)

if(NOT LINENOISE_LIBRARY OR NOT LINENOISE_INCLUDE_DIR)
    message(FATAL_ERROR "linenoise library or headers not found!")
endif()

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    ${SDL2_INCLUDE_DIRS}
    ${LINENOISE_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${LINENOISE_LIBRARY}
)

if (ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release build")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -O2)
endif()

option(ENABLE_SANITIZER_ADDRESS "Enable Address Sanitizer" OFF)
option(ENABLE_SANITIZER_UB "Enable Undefined Behavior Sanitizer" OFF)

if(ENABLE_SANITIZER_ADDRESS)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
    message(STATUS "Address Sanitizer enabled")
endif()

if(ENABLE_SANITIZER_UB)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=undefined)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=undefined)
    message(STATUS "Undefined Behavior Sanitizer enabled")
endif()

if(DEFINED COMPILER)
    if(COMPILER STREQUAL "gcc")
        set(CMAKE_CXX_COMPILER g++)
    elseif(COMPILER STREQUAL "clang")
        set(CMAKE_CXX_COMPILER clang++)
    else()
        message(WARNING "Unsupported compiler: ${COMPILER}. Using default compiler.")
    endif()
endif()

message(STATUS "Using C++ compiler: ${CMAKE_CXX_COMPILER}")
