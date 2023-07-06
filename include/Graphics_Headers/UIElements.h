#ifndef UIELEMENTS_H
#define UIELEMENTS_H

// Standard Libraries
#include <iostream>
#include <filesystem>
#include <memory>
#include <vector>
#include <string>

// Graphics Libraries
#include "imgui.h"

class FolderUI {

public:
FolderUI();
~FolderUI();

void SetupWindow();
std::filesystem::path GetTargetPath();

private:
std::vector<std::filesystem::path> currentPathsVector;
std::filesystem::path selectedPath = std::filesystem::current_path();
std::filesystem::path endPath{""};

void LoopDirectory();
void ReverseDirectory();
void QueryDirectory();

};

// End of Folder UI

class ElementsBuilder {
public:
ElementsBuilder();
~ElementsBuilder();

float* SetColor(float color[]);

private:

};


#endif
