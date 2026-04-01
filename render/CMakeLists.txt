set(CMAKE_CXX_STANDARD 20)

add_library(orbit-render STATIC render.cpp)

target_link_libraries(orbit-render PUBLIC orbit-backend)