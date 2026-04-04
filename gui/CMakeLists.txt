set(CMAKE_CXX_STANDARD 20)

add_executable(orbit-gui gui.cpp)

target_link_libraries(orbit-color PUBLIC orbit-backend)
target_include_directories(orbit-gui PUBLIC ${CMAKE_SOURCE_DIR})