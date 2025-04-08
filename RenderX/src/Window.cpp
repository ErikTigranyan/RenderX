#include "Window.h"

// std
#include <stdexcept>

namespace rex {
	Window::Window(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
		initWindow();
	}

	Window::~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this); // allows us to pair glfw window object with an arbitrary pointer value which in this case was set to be the parent window object 
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback); // allows us to register a callback function that whenever the window is resized the function will be called with the arguments being the window pointer and the window's new width and height
	}

	void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void Window::framebufferResizeCallback(GLFWwindow* glfw_window, int width, int height) {
		auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
		window->framebufferResized = true;
		window->width = width;
	}

} // namspace rex