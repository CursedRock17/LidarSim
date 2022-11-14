add_executable(Graphics Graphics.cpp)

find_package(glad CONFIG REQUIRED)

target_link_libraries(src
PUBLIC
glad::glad
)


