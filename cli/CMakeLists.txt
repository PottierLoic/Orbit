set(CMAKE_CXX_STANDARD 20)

add_executable(orbit-cli cli.cpp)

target_link_libraries(orbit-cli PUBLIC orbit-backend)
target_include_directories(orbit-cli PUBLIC ${CMAKE_SOURCE_DIR})