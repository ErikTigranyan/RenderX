cmake_minimum_required(VERSION 3.10)
project(RenderX VERSION 1.0 LANGUAGES CXX)

if (DEFINED ENV{VULKAN_SDK})
    set(VULKAN_SDK_PATH $ENV{VULKAN_SDK})
else()
    message(FATAL_ERROR "Please Install Vulkan SDK and put VULKAN_SDK env variable to Vulkan version folder!")
endif()

add_subdirectory(RenderX)
add_subdirectory(Dependencies/glfw)
