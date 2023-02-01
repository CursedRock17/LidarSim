cmake_minimum_required(VERSION 3.23)
project(LidarSim VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_TOOLCHAIN_FILE "/Users/cursedrock17/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

if(${GLAD_FOUND})
	message("Found it")
else()
	message("Didn't Find Glad")
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -O3)

add_subdirectory(include)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME}
PRIVATE
Graphics
Graphics_Headers

Camera
Camera_Headers

Gizmos
Gizmos_Headers

Application_Headers
Application

glad::glad
glfw
glm::glm
imgui::imgui
assimp::assimp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
"${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/include"
"${PROJECT_SOURCE_DIR}/src"
)

