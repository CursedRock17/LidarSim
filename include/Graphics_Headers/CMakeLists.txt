add_library(include INTERFACE Graphics.h)

find_package(glad CONFIG REQUIRED)

target_link_libraries(include
INTERFACE
glad::glad
)
