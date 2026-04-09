set(CMAKE_CXX_STANDARD 20)

set_source_files_properties(stb_impl.cpp PROPERTIES COMPILE_FLAGS "-w")

add_library(orbit-export stb_impl.cpp image_export.cpp video_export.cpp)

target_link_libraries(orbit-export PUBLIC orbit-color)
target_include_directories(orbit-export PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(orbit-export PRIVATE ${CMAKE_SOURCE_DIR}/external/stb)
