set(CMAKE_CXX_STANDARD 20)

add_library(orbit-backend STATIC cpu_single_threaded.cpp cpu_multi_threaded.cpp)

target_link_libraries(orbit-backend PUBLIC orbit-core)
target_include_directories(orbit-backend PUBLIC ${CMAKE_SOURCE_DIR})