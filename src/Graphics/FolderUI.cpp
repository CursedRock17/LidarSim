#include "../../include/Graphics_Headers/FolderUI.h"

FolderUI::FolderUI(){}
FolderUI::~FolderUI(){}

void FolderUI::SetupWindow()
{
	if(ImGui::BeginPopupModal("FolderFinder")){
		ImGui::Text("List Files");
		
		//Gain access to all the current files and folder underneath our selected path
		LoopDirectory();

		//Create a Selectable Object for each path
		for(auto path : currentPathsVector){
			if(ImGui::Selectable((path.filename()).c_str(), false, ImGuiSelectableFlags_DontClosePopups, ImVec2(325.0f, 10.0f) )){
				selectedPath = path;
				//Once finished looking through all the files allow the program to refresh
				currentPathsVector.clear();
				
				//If the file has an extension then we've found a file to select otherwise it would be another folder to recur through
			 	if(path.has_extension()){
					endPath = path;
					selectedPath = path.parent_path();	
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::Spacing();
		}

		//Add a Close Button so we can easily escape
		ImGui::Separator();
		if(ImGui::Button("Close")){
			ImGui::CloseCurrentPopup();
		}
	
		ImGui::SameLine();
		if(ImGui::Button("Back")){
			ReverseDirectory();
		}

		ImGui::EndPopup();
	}
}


void FolderUI::LoopDirectory()
{
	if(currentPathsVector.size() == 0){
		for(auto const& contents : std::filesystem::directory_iterator{selectedPath}){
			currentPathsVector.push_back(contents.path());
		}
	}
}


void FolderUI::ReverseDirectory()
{
	//Go back by reversing the path then clear the vector we had
	selectedPath = selectedPath.parent_path();
	currentPathsVector.clear();

	for(auto const& contents : std::filesystem::directory_iterator{selectedPath}){
		currentPathsVector.push_back(contents.path());
	}
	
}

std::filesystem::path FolderUI::GetTargetPath()
{
	return endPath;
}

void FolderUI::QueryDirectory()
{
	//Going to take the entire directory and section it out into groups of 100 so the search doesn't take an abmissmal amount of time by tracking how far we've scrolled
	

}

