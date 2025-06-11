#pragma once

#include <string>

#include <vulkan/vulkan_core.h>

#include "domkrat3d/_default.hpp"
#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL

#include <vector>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class SimpleBasicApplication {
  public:
	const int WIDTH = 800;
	const int HEIGHT = 600;
	const char* TITLE = "SimpleBasicApplication";
	static std::string DebugIndent;

	void run();

	/**
	 * @brief VKAPI debug callback
	 *
	 * @param message_severity message severity
	 * @param message_type message type
	 * @param p_callback_data callback data
	 * @param p_user_data user data
	 * @return VkBool32 boolean (VK_FALSE)
	 **/
	static VKAPI_ATTR auto VKAPI_CALL
	debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
				   VkDebugUtilsMessageTypeFlagsEXT message_type,
				   const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
				   void* p_user_data) -> VkBool32;

  private:
	GLFWwindow* window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debug_messenger;

	/**
	 * @brief Check validation layers support
	 *
	 * @return true validation layers supported
	 * @return false not supported
	 **/
	auto check_validation_layer_support() -> bool;

	/**
	 * @brief Get the required extensions
	 *
	 * @return std::vector<const char*> required extensions list
	 **/
	auto get_required_extensions() -> std::vector<const char*>;

	/**
	 * @brief Populate debug messenger CreateInfo
	 *
	 * @param create_info createInfo object
	 **/
	void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& create_info);

	/**
	 * @brief Init GLFW Window
	 *
	 **/
	void init_window();

	/**
	 * @brief Init vulkan
	 *
	 **/
	void init_vulkan();

	/**
	 * @brief Set the up debug callback object
	 *
	 **/
	void setup_debug_callback();

	/**
	 * @brief Main application loop
	 *
	 **/
	void main_loop();

	/**
	 * @brief Cleanup resources
	 *
	 **/
	void cleanup();

	/**
	 * @brief Create a vulkan instance object
	 *
	 **/
	void create_instance();
};

/**
 * @brief Open SimpleBasicApplication
 *
 * @param application simplebasicapplication pointer
 * @return int status code
 **/
auto open_application(SimpleBasicApplication* application) -> int;
