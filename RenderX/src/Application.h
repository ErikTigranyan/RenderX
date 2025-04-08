#pragma once

#include "Window.h"
#include "Pipeline.h"
#include "Device.h"
#include "SwapChain.h"
#include "Model.h"

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
		void loadModels();
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void freeCommandBuffers();
		void drawFrame();
		void recreateSwapChain();
		void recordCommandBuffer(int imageIndex);

		Window window {WIDTH, HEIGHT, "Hello Vulkan!"};
		Device device {window};
		std::unique_ptr<SwapChain> swapChain; // gets updated width and height
		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		std::vector <VkCommandBuffer> commandBuffers;
		std::unique_ptr<Model> model;
	};
}