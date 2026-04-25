set(CMAKE_CXX_STANDARD 20)

add_executable(orbit-gui main.cpp app.cpp ui.cpp renderer.cpp)

target_link_libraries(orbit-gui PRIVATE
        orbit-backend
        orbit-color
        orbit-export
        glad
        imgui
        glfw
)

target_include_directories(orbit-gui PUBLIC ${CMAKE_SOURCE_DIR})

target_compile_definitions(orbit-gui PRIVATE SHADER_PATH="${CMAKE_SOURCE_DIR}/shaders/")