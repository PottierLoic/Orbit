set(CMAKE_CXX_STANDARD 20)

add_library(orbit-backend STATIC backend.cpp)

target_link_libraries(orbit-backend PUBLIC orbit-core)