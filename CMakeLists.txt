cmake_minimum_required(VERSION 3.23)
project(LidarSim VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(src)
add_subdirectory(include)


target_link_libraries(${PROJECT_NAME}
PUBLIC
src
include
)


target_include_directories(${PROJECT_NAME}
PUBLIC
"${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/src"
"${PROJECT_SOURCE_DIR}/include"
)


