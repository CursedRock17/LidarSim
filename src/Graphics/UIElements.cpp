#include "../../include/Graphics_Headers/UIElements.h"
#include <memory>

FolderUI::FolderUI(){}
FolderUI::~FolderUI(){}

void FolderUI::SetupWindow(const std::string& FolderName)
{
//Gain access to all the current files and folder underneath our selected path
	LoopDirectory();
	if(ImGui::BeginPopupModal(FolderName.c_str())){
		ImGui::Text("List Files");
		//Create a Selectable Object for each path cannot let this path disappear or we lose access to a selectable element
		for(auto const& path : currentPathsVector){
			if(ImGui::Selectable(path.filename().c_str(), false, ImGuiSelectableFlags_DontClosePopups, ImVec2(325.0f, 10.0f) )){
				selectedPath = path;

				//If the file has an extension then we've found a file to select otherwise it would be another folder to recur through
			 	if(path.has_extension()){
					endPath = path;
					selectedPath = path.parent_path();
					ImGui::CloseCurrentPopup();
				}
                else {
                //Once finished looking through all the files allow the program to refresh
				currentPathsVector.clear();
                SetupWindow(FolderName);
                break;
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

// End of the folder UI

// Elements Builder Class
ElementsBuilder::ElementsBuilder(){}
ElementsBuilder::~ElementsBuilder(){}

float* ElementsBuilder::SetColor(float color[]){

		ImGui::ColorEdit3("Color: ", color);
        ImGui::Separator();
        return color;
}

InputFloatState ElementsBuilder::SetRotation(float rotation[]){
        // Rotation Setter
        InputFloatState rotationState;
        float rotations[3] = { rotation[0], rotation[1], rotation[2]  };
		ImGui::InputFloat3("Rotations X Y Z: ", rotations);
		if(ImGui::IsItemDeactivatedAfterEdit()){
            rotationState.activated = true;
			//We have to create a updated Rotation because otherwise we woould just continous apply the new value instead of update to get that desired value
			//Take the Gizmos value then subtract that new value to rotate the object, x much more compared to the original where x is the new value, then just update
			rotation[0]  = rotations[0] - rotation[0];
			rotation[1]  = rotations[1] - rotation[1];
			rotation[2]  = rotations[2] - rotation[2];

            rotation[3] = rotations[0];
            rotation[4] = rotations[1];
            rotation[5] = rotations[2];
        }


        ImGui::Separator();
        rotationState.floats = rotation;
        return rotationState;
}

InputFloatState ElementsBuilder::SetTranslation(float translation[]){
        //Translation Setter
        InputFloatState translationState;
		float translations[3] = { translation[0], translation[1], translation[2] };
	    ImGui::InputFloat3("Translations X Y Z: ", translations);
		if(ImGui::IsItemDeactivatedAfterEdit()){
            translationState.activated = true;
			//We have to create a updated Translation because otherwise we woould just continous apply the new value instead of update to get that desired value
			//Take the Gizmos value then subtract that new value to displace the object, x much more compared to the original where x is the new value, then just update
			translation[0] = translations[0] - translation[0];
			translation[1] = -1.0f * (translations[1] - translation[1]);
			translation[2] = translations[2] - translation[2];

            translation[3] = translations[0];
            translation[4] = translations[1];
            translation[5] = translations[2];
        }

	ImGui::Separator();
    translationState.floats = translation;
    return translationState;
}

InputFloatState ElementsBuilder::SetScale(float scale[]){
		//Scale Setter
        InputFloatState scaleState;
        float scales[3] = { scale[0], scale[1], scale[2] };
		ImGui::InputFloat3("Scale X Y Z: ", scales);
		if(ImGui::IsItemDeactivatedAfterEdit()){
            scaleState.activated = true;
			//We have to create a updated Scale because 0 will create an irreverisble effect on the model matrix
			if(scales[0] == 0.0f)
				scales[0] = 0.00000001f;
			if(scales[1] == 0.0f)
				scales[1] = 0.00000001f;
			if(scales[2] == 0.0f)
				scales[2] = 0.00000001f;

			//Take the Gizmos value then subtract that new value to scale the object, x much more compared to the original where x is the new value, then just update
		 scale[0] = scales[0] / scale[0];
		 scale[1] = scales[1] / scale[1];
		 scale[2] = scales[2] / scale[2];

         scale[3] = scales[0];
         scale[4] = scales[1];
         scale[5] = scales[2];
        }
		ImGui::Separator();
        scaleState.floats = scale;
        return scaleState;
}

float* ElementsBuilder::SetStrengths(float strength[]){
		ImGui::DragFloat3("Material Strengths", strength, 0.01f, 0.0f, 1.0f);
        return strength;
}

float ElementsBuilder::SetShiny(float shiny){
		ImGui::InputFloat("Specular Shine", &shiny);
        return shiny;
}

void ElementsBuilder::CreateFolder(const std::string& ButtonName){
		if(ImGui::Button(ButtonName.c_str())){
			//Open up the Folder Finder Window that we will make ourselves
			ImGui::OpenPopup("ElementFolder");
		}
		ImGui::Separator();
}
// Elements Builder Class End

