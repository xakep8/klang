cmake_minimum_required(VERSION 3.25)

project(klang VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(KLANG_BUILD_TESTS "Build klang tests" ON)

add_library(klang_core STATIC)

target_compile_features(klang_core PUBLIC cxx_std_20)

target_include_directories(klang_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(klang_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(klang_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(klang_cli)
target_link_libraries(klang_cli PRIVATE klang_core)

add_subdirectory(lexer)
# add_subdirectory(parser)
# add_subdirectory(ast)
# add_subdirectory(compiler)
# add_subdirectory(debug)
# add_subdirectory(vm)
# add_subdirectory(cli)

if(KLANG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()