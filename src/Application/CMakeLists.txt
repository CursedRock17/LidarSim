add_library(Application Application.cpp Layer.cpp)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(Application
PUBLIC
glad::glad
glfw
)
