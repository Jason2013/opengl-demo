cmake_minimum_required(VERSION 3.4)

project(OpenGL_DEMO)

if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
   set(GLEW_ARCH x64) 
   set(GLFW_ARCH win64) 
else() 
   set(GLEW_ARCH Win32) 
   set(GLFW_ARCH win32) 
endif() 

# https://github.com/rpavlik/cmake-modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/external/cmake-modules)
cmake_policy(SET CMP0026 OLD)
include(CreateLaunchers)

include_directories(
    external/glew-win32-binaries/include
    external/glfw-${GLFW_ARCH}-binaries/include
    external/glm
    ${CMAKE_SOURCE_DIR}/src
)

add_executable(DEMO
    src/main.cpp
    src/shader.cpp
    src/globjs.cpp
    src/objloader.cpp
    src/texture.cpp
    src/sphere.cpp
    src/demo00/demo00.cpp
    src/demo01/demo01.cpp
    src/demo02/demo02.cpp
)

set_target_properties(DEMO PROPERTIES
    COMPILE_DEFINITIONS "GLEW_STATIC;_CRT_SECURE_NO_WARNINGS"
)

target_link_libraries(DEMO
    OpenGL32.lib
    ${CMAKE_SOURCE_DIR}/external/glew-win32-binaries/lib/Release/${GLEW_ARCH}/glew32s.lib
    ${CMAKE_SOURCE_DIR}/external/glfw-${GLFW_ARCH}-binaries/lib-vc2015/glfw3.lib
)

create_target_launcher(DEMO WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
