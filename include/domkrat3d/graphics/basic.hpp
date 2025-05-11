#pragma once

#include <vector>
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <vulkan/vulkan.h>
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
		GLFWwindow* window;

		// Vulkan Instance
		VkInstance instance;

		VkDebugUtilsMessengerEXT debugMessenger;

		static VKAPI_ATTR auto VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
										const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) -> VkBool32;

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
		 * An instance is the link between your program and the Vulkan library, and to create it, you will
		 * need to provide the driver with some information about your program.
		 **/
		void create_instance();

		auto check_validation_layer_support() -> bool;

		auto enable_validation_layers() -> bool;

		void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		void setup_debug_messenger();

		auto get_required_extensions() -> std::vector<const char*>;
};

/**
 * @brief Open DomkratTriangleApplication
 * 
 * @param application Domkrat triangle application
 * @return int status code
 **/
auto open_application(DomkratTriangleApplication* application) -> int;
