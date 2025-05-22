#include "Application.h"
#include "SimpleRenderSystem.h"

// libs
#define	GLM_FORCE_RADIANS
#define	GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

//std
#include <stdexcept>
#include <cassert>
#include <array>

namespace rex {

	Application::Application() { loadGameObjects(); }

	Application::~Application() {}

	void Application::run() {
		SimpleRenderSystem simpleRenderSystem{ device, renderer.getSwapChainRenderPass() };
		while (!window.shouldClose()) {
			glfwPollEvents();

			if (auto commandBuffer = renderer.beginFrame()) {
				renderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
				renderer.endSwapChainRenderPass(commandBuffer);
				renderer.endFrame();
			}
		}

		vkDeviceWaitIdle(device.device());
	}

	void Application::loadGameObjects() {
		std::vector<Model::Vertex> vertices{
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};

		auto model = std::make_shared<Model>(device, vertices); // allows us to have one model insance that can be used by multiple objects

		auto triangle = GameObject::createGameObject();
		triangle.model = model;
		triangle.color = {.1f, .8f, .1f}; // greenish color
		triangle.transform2d.translation.x = .2f; // moves the triangle slightly to the right
		triangle.transform2d.scale = { 2.f, .5f };
		triangle.transform2d.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}
} // namespace rex