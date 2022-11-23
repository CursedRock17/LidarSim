add_library(Camera_Headers INTERFACE Camera.h)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(Camera_Headers
INTERFACE
glad::glad
glfw
glm::glm
)
