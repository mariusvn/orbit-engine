cmake_minimum_required(VERSION 3.0)
project(OrbitEngine)

set(CMAKE_CXX_STANDARD 17)

if (NOT DEFINED GLFW_LOCATION)
    message(FATAL_ERROR "Please specify GLFW_LOCATION")
endif()

if (NOT DEFINED GLAD_LOCATION)
    message(FATAL_ERROR "Please specify GLAD_LOCATION")
endif()

if (NOT DEFINED GLM_LOCATION)
    message(FATAL_ERROR "Please specify GLM_LOCATION")
endif()

if (NOT DEFINED IMGUI_LOCATION)
    message(FATAL_ERROR "Please specify IMGUI_LOCATION")
endif()

if (NOT DEFINED ASSIMP_LOCATION)
    message(FATAL_ERROR "Please specify ASSIMP_LOCATION")
endif()

file(GLOB src src/*.cpp src/**/*.cpp)

if (NOT DEFINED BUILD_STATIC)
    set(LIB_BUILD_TYPE SHARED)
else()
    set(LIB_BUILD_TYPE STATIC)
endif()

add_library(OrbitEngine ${LIB_BUILD_TYPE} ${src})
set_target_properties(OrbitEngine PROPERTIES OUTPUT_NAME "orbit")

target_link_libraries(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${GLFW_LOCATION}/lib-static-ucrt/glfw3.dll")
target_include_directories(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${GLFW_LOCATION}/include")

target_link_libraries(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${GLAD_LOCATION}/lib/libglad.dll")
target_include_directories(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${GLAD_LOCATION}/include")

target_include_directories(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${GLM_LOCATION}")

target_link_libraries(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${IMGUI_LOCATION}/bin/libimgui.dll")
target_include_directories(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${IMGUI_LOCATION}/include")

target_link_libraries(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${ASSIMP_LOCATION}/bin/libassimp.dll")
target_include_directories(OrbitEngine PUBLIC "${CMAKE_SOURCE_DIR}/${ASSIMP_LOCATION}/include")

target_include_directories(OrbitEngine PUBLIC ./include)


add_custom_command(TARGET OrbitEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/${GLFW_LOCATION}/lib-static-ucrt/glfw3.dll"
        "${CMAKE_BINARY_DIR}/glfw3.dll")
add_custom_command(TARGET OrbitEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/${GLAD_LOCATION}/lib/libglad.dll"
        "${CMAKE_BINARY_DIR}/libglad.dll")
add_custom_command(TARGET OrbitEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/${IMGUI_LOCATION}/bin/libimgui.dll"
        "${CMAKE_BINARY_DIR}/libimgui.dll")
add_custom_command(TARGET OrbitEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/${ASSIMP_LOCATION}/bin/libassimp.dll"
        "${CMAKE_BINARY_DIR}/libassimp.dll")

file(GLOB demo_src demo/*.cpp demo/**/*.cpp)
add_executable(Demo ${demo_src})
target_link_libraries(Demo PUBLIC OrbitEngine)
target_include_directories(Demo PUBLIC ./include)