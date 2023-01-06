#include "../../include/Graphics_Headers/FolderUI.h"

void SetupWindow()
{

	if(ImGui::BeginPopup("FolderFinder")){
		ImGui::Text("List Files");
		for(auto const& path : currentPathsVector){
		ImGui::Selectable("path", &show);
		}
		ImGui::EndPopup();
	}
}


void LoopDirectory()
{
	for(auto const& contents : std::filesystem::directory_iterator{"src"}){
		std::cout << contents.path() << std::endl;
		currentPathsVector.push_back(contents.path());
	}
}


