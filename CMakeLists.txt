cmake_minimum_required(VERSION 3.21)
project(orbit)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Werror)

add_subdirectory(core)
add_subdirectory(backend)
add_subdirectory(color)
add_subdirectory(cli)
add_subdirectory(gui)
add_subdirectory(export)

include(CTest)
add_subdirectory(tests)
