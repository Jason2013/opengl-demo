cmake_minimum_required(VERSION 3.4)

project(OpenGL_DEMO)

# https://github.com/rpavlik/cmake-modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} C:/chenchang/dev/cmake-modules)
cmake_policy(SET CMP0026 OLD)
include(CreateLaunchers)

include_directories(C:/chenchang/dev/glfw-3.1.2/include
    C:/chenchang/dev/glew-1.13.0/include
    common
)

link_libraries(opengl32.lib
    C:/chenchang/dev/glfw-3.1.2/bld/src/$<$<CONFIG:Debug>:Debug>$<$<NOT:$<CONFIG:Debug>>:Release>/glfw3.lib
    C:/chenchang/dev/glew-1.13.0/build/cmake/bld/lib/$<$<CONFIG:Debug>:Debug>$<$<NOT:$<CONFIG:Debug>>:Release>/libglew32$<$<CONFIG:Debug>:d>.lib
)

add_executable(DEMO
    src/main.cpp
    src/shader.cpp
    src/globjs.cpp
)

set_target_properties(DEMO PROPERTIES
    COMPILE_DEFINITIONS GLEW_STATIC
)

create_target_launcher(DEMO WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
