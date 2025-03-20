#pragma once

#include "Window.h"
#include "Pipeline.h"

namespace rex {
	class Application {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		Window window = Window(WIDTH, HEIGHT, "Hello Vulkan!");
		Pipeline Pipeline{"../shaders/simple_shader.vert.spv", "../shaders/simple_shader.frag.spv"};
	};
}