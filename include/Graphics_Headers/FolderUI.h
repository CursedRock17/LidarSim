#ifndef FOLDERUI_H
#define FOLDERUI_H

// Standard Libraries
#include <iostream>
#include <filesystem>
#include <vector>

// Graphics Libraries
#include "imgui.h"

void SetupWindow();
void LoopDirectory();

const bool show{true};
std::vector<std::filesystem::path> currentPathsVector;

#endif
