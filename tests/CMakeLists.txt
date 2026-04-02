include(FetchContent)

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.5.0
)
FetchContent_MakeAvailable(doctest)

add_executable(orbit-tests
        core/test_complex.cpp
        core/test_iterate.cpp
        core/test_mandelbrot.cpp
        main.cpp
)

target_link_libraries(orbit-tests PRIVATE
        orbit-core
        doctest::doctest
)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(orbit-tests)