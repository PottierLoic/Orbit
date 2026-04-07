include(FetchContent)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.5
        GIT_SHALLOW TRUE
)
set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(orbit-benchmark benchmark_backends.cpp)

target_link_libraries(orbit-benchmark PRIVATE orbit-backend orbit-color benchmark::benchmark)

target_include_directories(orbit-benchmark PRIVATE ${CMAKE_SOURCE_DIR})