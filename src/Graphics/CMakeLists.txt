add_library(Graphics Graphics.cpp UI.cpp)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(Graphics
PUBLIC
glad::glad
glfw
)
