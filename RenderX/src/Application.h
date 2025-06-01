#pragma once

#include "Window.h"
#include "Device.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Descriptors.h"

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

		// order of declarations matters
		std::unique_ptr<DescriptorPool> globalPool{}; // any descriptors that should be shared by multiple systems can use this object 
		GameObject::Map gameObjects;
	};
} // namespace rex