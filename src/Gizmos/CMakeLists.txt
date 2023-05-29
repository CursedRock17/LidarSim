add_library(Gizmos Gizmos.cpp Mesh.cpp GizmosExtensions.cpp)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
#find_package(assimp CONFIG REQUIRED)


target_link_libraries(Gizmos
PUBLIC
glad::glad
glfw
glm::glm
assimp::assimp
)
