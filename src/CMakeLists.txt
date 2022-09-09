add_library(src Lidar.cpp Graphics.cpp)

find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(src
PUBLIC
glad::glad
SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static
)


