add_library(Space Space.cpp)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(Space
PUBLIC
glad::glad
glfw
)
