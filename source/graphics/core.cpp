#include <cstdint>
#include <iostream>

#include "domkrat3d/graphics/core.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include "domkrat3d/tracelogger.hpp"
#include "domkrat3d/utils/random.hpp"

#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// Non-public Functions
namespace {
	void print_vulkan_extensions_count() {
		LOG_TRACE

		/**
		 * @brief Print supported Vulkan Extensions count
		 **/
		uint32_t extension_count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

		std::cout << extension_count << " extensions supported\n";
	}
}	 // namespace

void init_glfw(bool resizable) {
	LOG_TRACE
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	if (resizable) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
}

auto create_window(int width, int height, const char* title) -> GLFWwindow* {
	LOG_TRACE

	return glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void terminate_window(GLFWwindow* window) {
	LOG_TRACE

	// Destroy window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
}

void poll_events_if_window_open(GLFWwindow* window, int width, int height) {
	LOG_TRACE

	glViewport(0, 0, width, height);

	// generate random color
	float red = generate_random_float();
	float blue = generate_random_float();
	float green = generate_random_float();

	while (glfwWindowShouldClose(window) == 0) {
		glfwPollEvents();

		// Render Color
		glClearColor(red, green, blue, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

void initialize_window(int width, int height, const char* title) {
	LOG_TRACE;

	init_glfw();	// init glfw

	GLFWwindow* window = create_window(width, height, title);	 // create window

	print_vulkan_extensions_count();	// print VK extensions count

	poll_events_if_window_open(window, width, height);	  // poll events

	terminate_window(window);
}
