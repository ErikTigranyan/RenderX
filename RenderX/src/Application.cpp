#include "Application.h"
#include "SimpleRenderSystem.h"
#include "Camera.h"
#include "KeyboardMovementController.h"
#include "Buffer.h"

// libs
#define	GLM_FORCE_RADIANS
#define	GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

//std
#include <chrono>
#include <stdexcept>
#include <cassert>
#include <array>
#include <numeric>

namespace rex {
	// this struct is the same as the simple push constant data
	struct GlobalUbo {
		glm::mat4 projectionView{1.f};
		glm::vec4 ambientLightColor{1.f, 1.f, 1.f, .02f}; // w is light intensity
		glm::vec3 lightPosition{-1.f};
		alignas(16) glm::vec4 lightColor{1.f}; // w is light intensity
	};

	Application::Application() { 
		globalPool = DescriptorPool::Builder(device)
			.setMaxSets(SwapChain::MAX_FRAMES_IN_FLIGHT)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
			.build();
		loadGameObjects();
	}

	Application::~Application() {}

	void Application::run() {
		// find lowest common multiple 
		auto minOffsetAlignment = std::lcm(
			device.properties.limits.minUniformBufferOffsetAlignment,
			device.properties.limits.nonCoherentAtomSize
		);
		std::vector<std::unique_ptr<Buffer>> uboBuffers(SwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < uboBuffers.size(); i++) {
			uboBuffers[i] = std::make_unique<Buffer>(
				device,
				sizeof(GlobalUbo),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
			uboBuffers[i]->map();
		}

		auto globalSetLayout = DescriptorSetLayout::Builder(device)
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT)
			.build();
		
		std::vector<VkDescriptorSet> globalDescriptorSets(SwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < globalDescriptorSets.size(); i++) {
			auto bufferInfo = uboBuffers[i]->descriptorInfo();
			DescriptorWriter(*globalSetLayout, *globalPool)
				.writeBuffer(0, &bufferInfo)
				.build(globalDescriptorSets[i]);
		}

		SimpleRenderSystem simpleRenderSystem{ 
			device,
			renderer.getSwapChainRenderPass(),
			globalSetLayout->getDescriptorSetLayout()
		};
        Camera camera{};

        auto viewerObject = GameObject::createGameObject();
		viewerObject.transform.translation.z = -2.5f;
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

		while (!window.shouldClose()) {
			glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = renderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);
			if (auto commandBuffer = renderer.beginFrame()) {
				int frameIndex = renderer.getFrameIndex();
				FrameInfo frameInfo{
					frameIndex,
					frameTime,
					commandBuffer,
					camera,
					globalDescriptorSets[frameIndex]
				};

				// UPDATE
				// here we will prepare and update objects and memory
				GlobalUbo ubo{};
				ubo.projectionView = camera.getProjection() * camera.getView();
				uboBuffers[frameIndex]->writeToBuffer(&ubo); 
				uboBuffers[frameIndex]->flush();
				// RENDER
				// here the draw calls will be recorded
				renderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(frameInfo, gameObjects);
				renderer.endSwapChainRenderPass(commandBuffer);
				renderer.endFrame();
			}
		}
		vkDeviceWaitIdle(device.device());
	}

 	void Application::loadGameObjects() {
        std::shared_ptr<Model> model = Model::createModelFromFile(device, "../../RenderX/models/flat_vase.obj");
		auto flatVase = GameObject::createGameObject();
		flatVase.model = model;
		flatVase.transform.translation = { -.5f, .5f, 0.f };
		flatVase.transform.scale = { 3.f, 1.5f, 3.f };
		gameObjects.push_back(std::move(flatVase));

		model = Model::createModelFromFile(device, "../../RenderX/models/smooth_vase.obj");
		auto smoothVase = GameObject::createGameObject();
		smoothVase.model = model;
		smoothVase.transform.translation = { .5f, .5f, 0.f };
		smoothVase.transform.scale = { 3.f, 1.5f, 3.f };
		gameObjects.push_back(std::move(smoothVase));

		model = Model::createModelFromFile(device, "../../RenderX/models/quad.obj");
		auto floor = GameObject::createGameObject();
		floor.model = model;
		floor.transform.translation = { 0.f, .5f, 0.f };
		floor.transform.scale = { 3.f, 1.f, 3.f };
		gameObjects.push_back(std::move(floor));
	}
} // namespace rex