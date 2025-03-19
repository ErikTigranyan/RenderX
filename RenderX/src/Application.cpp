#include "Application.h"

namespace rex {
	void Application::run() {
		while (!window.shouldClose()) {
			glfwPollEvents();
		}
	}
} // namespace rex