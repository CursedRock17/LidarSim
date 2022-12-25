#include "../../include/Application_Headers/Layer.h"

Layer::Layer()
{

}

Layer::~Layer()
{

}

void Layer::OnLayerInit()
{
//	UiRef->SetupMenu();	
}


void Layer::OnLayerDestroy()
{

}


void Layer::OnLayerUpdate()
{
//	UiRef->MenuLoop();
}

void Layer::SetupUI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> applicationGizmos)	
{
//	UiRef = std::make_shared<UI>(window, windowHeight, windowWidth, applicationGizmos);	
}
