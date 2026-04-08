set(CMAKE_CXX_STANDARD 20)

add_library(orbit-color STATIC apply.cpp)

target_link_libraries(orbit-color PUBLIC orbit-backend)
target_include_directories(orbit-color PUBLIC ${CMAKE_SOURCE_DIR})