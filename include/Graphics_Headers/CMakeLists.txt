add_library(Graphics_Headers INTERFACE Graphics.h UI.h)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(Graphics_Headers
INTERFACE
glad::glad
glfw
)
