set(CMAKE_CXX_STANDARD 20)

add_executable(orbit-cli cli_export_video.cpp)

target_link_libraries(orbit-cli PUBLIC orbit-backend orbit-export)

target_include_directories(orbit-cli PUBLIC ${CMAKE_SOURCE_DIR})