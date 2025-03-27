#include "Application.h"

//std
#include <stdexcept>

namespace rex {
	Application::Application() {
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	Application::~Application() {
		vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
	}

	void Application::run() {
		while (!window.shouldClose()) {
			glfwPollEvents();
		}
	}
	void Application::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create pipeline layout!");
		}

	}
	void Application::createPipeline() {
		auto pipelineConfig = Pipeline::defaultPipelineConfigInfo(swapChain.width(), swapChain.height());
		pipelineConfig.renderPass = swapChain.getRenderPass(); // describes the structure and format of our frame buffer objects and thier attachments
		pipelineConfig.pipelineLayout = pipelineLayout;
		pipeline = std::make_unique<Pipeline>(device, "../../RenderX/shaders/simple_shader.vert.spv", "../../RenderX/shaders/simple_shader.frag.spv", pipelineConfig);
	};

	void Application::createCommandBuffers() {};
	void Application::drawFrame() {};
} // namespace rex