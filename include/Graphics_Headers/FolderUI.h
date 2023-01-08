#ifndef FOLDERUI_H
#define FOLDERUI_H

// Standard Libraries
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>


// Graphics Libraries
#include "imgui.h"

class FolderUI {

public:
FolderUI();
~FolderUI();

void SetupWindow();
std::filesystem::path* GetTargetPath();

private:
std::vector<std::filesystem::path> currentPathsVector;
std::filesystem::path selectedPath = std::filesystem::current_path();
std::filesystem::path* endPath{nullptr};

void LoopDirectory();
void ReverseDirectory();

};

#endif
