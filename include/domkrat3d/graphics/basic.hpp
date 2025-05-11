#pragma once

#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <GLFW/glfw3.h>

class DomkratTriangleApplication {
  public:
	// Title
	char* title = "DomkratTriangleApplication";

	int width = 800;
	int height = 600;

	/**
	 * @brief Run a Application
	 **/
	void run();

  private:
	// GLFW Window
	GLFWwindow* m_window {};

	// Vulkan Instance
	VkInstance m_instance {};

	/**
	 * @brief Init GLFW and create window
	 **/
	void init_window();

	/**
	 * @brief Init vulkan
	 **/
	void init_vulkan();

	/**
	 * @brief Main application work loop
	 **/
	void main_loop();

	/**
	 * @brief Cleanup application
	 **/
	void cleanup();

	/**
	 * @brief Create a vulkan instance object
	 **/
	void create_instance();
};

/**
 * @brief Open DomkratTriangleApplication
 *
 * @param application Domkrat triangle application
 * @return int status code
 **/
auto open_application(DomkratTriangleApplication* application) -> int;
