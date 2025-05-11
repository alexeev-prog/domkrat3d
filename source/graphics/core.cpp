#include <cstdint>
#include <iostream>

#include "domkrat3d/graphics/core.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// Non-public Functions
namespace {
	void print_vulkan_extensions_count() {
		/**
		 * @brief Print supported Vulkan Extensions count
		 **/
		uint32_t extension_count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

		std::cout << extension_count << " extensions supported\n";
	}
}	 // namespace

void init_glfw(bool resizable) {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	if (resizable) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
}

auto create_window(int width, int height, const char* title) -> GLFWwindow* {
	return glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void terminate_window(GLFWwindow* window) {
	// Destroy window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
}

void poll_events_if_window_open(GLFWwindow* window) {
	// if window is not closed, poll glfw events
	while (glfwWindowShouldClose(window) == 0) {
		glfwPollEvents();
	}
}

void initialize_window(int width, int height, const char* title) {
	init_glfw();	// init glfw

	GLFWwindow* window = create_window(width, height, title);	 // create window

	print_vulkan_extensions_count();	// print VK extensions count

	poll_events_if_window_open(window);	   // poll events

	terminate_window(window);
}
