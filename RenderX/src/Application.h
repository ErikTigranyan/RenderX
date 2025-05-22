#pragma once

#include "Window.h"
#include "Device.h"
#include "Renderer.h"
#include "GameObject.h"

//std
#include <memory>
#include <vector>

namespace rex {
	class Application {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		Application();
		~Application();

		Application(const Application&) = delete;
		Application &operator = (const Application&) = delete;

		void run();

	private:
		void loadGameObjects();

		Window window {WIDTH, HEIGHT, "Hello Vulkan!"};
		Device device {window};
		Renderer renderer{ window, device };

		std::vector<GameObject> gameObjects;
	};
} // namespace rex