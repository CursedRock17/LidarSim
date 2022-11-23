add_library(Camera Camera.cpp)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(Camera
PUBLIC
glad::glad
glfw
glm::glm
)
