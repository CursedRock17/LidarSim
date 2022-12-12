add_library(Graphics_Headers INTERFACE Graphics.h UI.h Imgui_OpenGL3_Impl.h)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
 

target_link_libraries(Graphics_Headers
INTERFACE
glad::glad
glfw
imgui::imgui
)
