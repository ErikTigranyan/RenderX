cmake_minimum_required(VERSION 3.10)
project(RenderX)

if (NOT DEFINED VULKAN_SDK_PATH)
    message(FATAL_ERROR "VULKAN_SDK_PATH is not defined. Make sure the parent CMakeLists.txt is correctly setting this variable.")
endif()

file(GLOB SOURCES "src/*.cpp" "src/*.h")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/glfw/include)
include_directories(${VULKAN_SDK_PATH}/Include)
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/glm/include)

link_directories(${VULKAN_SDK_PATH}/Lib)

add_executable(RenderX ${SOURCES})

target_link_libraries(RenderX
    PRIVATE
        glfw
	glm
        ${VULKAN_SDK_PATH}/Lib/vulkan-1.lib
)
