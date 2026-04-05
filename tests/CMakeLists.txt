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
        core/test_julia.cpp
        color/test_interpolation.cpp
        color/test_palette.cpp
        main.cpp
)

target_link_libraries(orbit-tests PRIVATE
        orbit-core
        orbit-color
        doctest::doctest
)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(orbit-tests)