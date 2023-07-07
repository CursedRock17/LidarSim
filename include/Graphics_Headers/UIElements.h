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

void SetupWindow(const std::string& FolderName);
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

struct InputFloatState {
    float* floats;
    bool activated = false;
};

class ElementsBuilder {
public:
ElementsBuilder();
~ElementsBuilder();

float* SetColor(float color[]);
InputFloatState SetRotation(float rotation[]);
InputFloatState SetTranslation(float translation[]);
InputFloatState SetScale(float scale[]);
float* SetStrengths(float strength[]);
float SetShiny(float shiny);
void CreateFolder(const std::string& ButtonName);

FolderUI ElementFolder;
private:


};


#endif
