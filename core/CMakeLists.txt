set(CMAKE_CXX_STANDARD 20)

add_library(orbit-core STATIC core.cpp)
target_include_directories(orbit-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(orbit-core PUBLIC ${CMAKE_SOURCE_DIR})