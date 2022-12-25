#ifndef LAYER_H
#define LAYER_H

#include <memory>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../include/Graphics_Headers/UI.h"
#include "../../include/Gizmos_Headers/Gizmos.h"
#include "imgui.h"

class Layer {
public:
Layer();
~Layer();

virtual void OnLayerInit();
virtual void OnLayerDestroy();
virtual void OnLayerUpdate();
void SetupUI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> applicationGizmos);

std::string LayerName{""};

private:

//ImGui Details
ImGuiIO* IO;
std::shared_ptr<UI> UiRef;

};

#endif
