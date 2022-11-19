add_library(Space_Headers INTERFACE Space.h)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(Space_Headers
INTERFACE
glad::glad
glfw
)
