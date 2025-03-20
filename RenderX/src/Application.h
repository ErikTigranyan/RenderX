#pragma once

#include "Window.h"
#include "Pipeline.h"
#include "Device.h"

namespace rex {
	class Application {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		Window window {WIDTH, HEIGHT, "Hello Vulkan!"};
		Device device {window};

		Pipeline Pipeline{device, "../../RenderX/shaders/simple_shader.vert.spv", "../../RenderX/shaders/simple_shader.frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};
}