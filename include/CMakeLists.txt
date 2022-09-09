add_library(include INTERFACE Lidar.h Graphics.h)

find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(include
INTERFACE
glad::glad
SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static
)
