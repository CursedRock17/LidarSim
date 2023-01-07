#ifndef FOLDERUI_H
#define FOLDERUI_H

// Standard Libraries
#include <iostream>
#include <filesystem>
#include <vector>

// Graphics Libraries
#include "imgui.h"

class FolderUI {

public:
FolderUI();
~FolderUI();

void SetupWindow();
void LoopDirectory();

private:
constexpr static bool show{true};
std::vector<std::filesystem::path> currentPathsVector;
std::filesystem::path selectedPath = std::filesystem::current_path();

};

#endif
