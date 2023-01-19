add_library(Application_Headers INTERFACE Application.h Universal_Consts.h)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(Application_Headers
INTERFACE
glad::glad
glfw
)
