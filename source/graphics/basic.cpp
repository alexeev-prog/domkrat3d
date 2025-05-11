#include <stdexcept>

#include <sys/types.h>
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <exception>
#include <iostream>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
// #include <stdexcept>
#include <cstdlib>

#include "domkrat3d/graphics/basic.hpp"
#include "domkrat3d/graphics/core.hpp"

void DomkratTriangleApplication::run() {
	init_window();
	init_vulkan();
	main_loop();
	cleanup();
}

void DomkratTriangleApplication::init_window() {
	init_glfw();

	window = create_window(width, height, DomkratTriangleApplication::title);
}

void DomkratTriangleApplication::init_vulkan() {
	create_instance();
}

void DomkratTriangleApplication::create_instance() {
    // Setup Vulkan Application Info
	VkApplicationInfo appInfo {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = DomkratTriangleApplication::title;
	appInfo.pEngineName = "Domkrat3D"; // engine
    
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

    // Make CreateInfo for VkInstance
	VkInstanceCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

    // Get GLFS Extensions Count
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

    // Create Vulkan Instance
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create Vulkan Instance!");
	}
}

void DomkratTriangleApplication::main_loop() {
	poll_events_if_window_open(window);
}

void DomkratTriangleApplication::cleanup() {
	vkDestroyInstance(instance, nullptr);

	terminate_window(window);
}

auto open_application(DomkratTriangleApplication* application) -> int {
	try {
		application->run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
