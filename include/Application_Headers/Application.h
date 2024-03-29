#ifndef APPLICATION_H
#define APPLICATION_H

// In Project Directories
#include "../../include/Gizmos_Headers/Gizmos.h"
#include "../../include/Graphics_Headers/Graphics.h"
#include "../../include/Graphics_Headers/UI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <thread>
#include <vector>


class Application {
public:
	Application();
	~Application();

	void ApplicationLoop();

private:
	GLFWwindow* window;
	static constexpr int windowWidth{800};
	static constexpr int windowHeight{600};

	std::vector<std::shared_ptr<Gizmos>> ApplicationGizmos;
	std::string mode{"Create"}; // The way the application is running whether, we clicked the play button or not

	void ApplicationLoad();
	void ApplicationClose();

	std::shared_ptr<Graphics> GraphicsRef;
	std::shared_ptr<MainUI> CurrentUI;
	std::thread mainThread;

	Framebuffer mFrame;
};

#endif
