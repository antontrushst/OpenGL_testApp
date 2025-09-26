cmake_minimum_required(VERSION 3.10)
project(testApp)

add_subdirectory(libs/glfw)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/glad.c
			       src/stb_image.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_SOURCE_DIR}/libs/glfw/include
           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL glfw)
