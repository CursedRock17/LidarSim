#include "../../include/Graphics_Headers/FolderUI.h"

FolderUI::FolderUI(){}
FolderUI::~FolderUI(){}

void FolderUI::SetupWindow()
{

	if(ImGui::BeginPopup("FolderFinder")){
		ImGui::Text("List Files");
		LoopDirectory();
		for(auto const& path : currentPathsVector){
		ImGui::Selectable("path", &show);
		}
		ImGui::EndPopup();
	}
}


void FolderUI::LoopDirectory()
{
	for(auto const& contents : std::filesystem::directory_iterator{selectedPath}){
		std::cout << contents.path() << std::endl;
		currentPathsVector.push_back(contents.path());
	}
}


