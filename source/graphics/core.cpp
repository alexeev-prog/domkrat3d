#include <cstdint>

#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "domkrat3d/graphics/core.hpp"

namespace {
	void init_glfw() {
		/**
		 * @brief Initalize a GLFW
		 **/
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	void print_vulkan_extensions_count() {
		/**
		 * @brief Print supported Vulkan Extensions count
		 *
		 **/
		uint32_t extension_count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

		std::cout << extension_count << " extensions supported\n";
	}
}	 // namespace

auto create_window(int width, int height, const char* title) -> GLFWwindow* {
	return glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void terminate_window(GLFWwindow* window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void poll_events_if_window_open(GLFWwindow* window) {
	while (glfwWindowShouldClose(window) == 0) {
		glfwPollEvents();
	}
}

void initialize_window(int width, int height, const char* title) {
	init_glfw();

	GLFWwindow* window = create_window(width, height, title);

	print_vulkan_extensions_count();

	poll_events_if_window_open(window);

	terminate_window(window);
}
