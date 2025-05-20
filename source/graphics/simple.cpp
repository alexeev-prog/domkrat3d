#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "domkrat3d/graphics/simple.hpp"

#include <vulkan/vulkan_core.h>

#include "domkrat3d/_default.hpp"
#include "domkrat3d/graphics/core.hpp"
#include "domkrat3d/tracelogger.hpp"

const std::vector<const char*> VALIDATION_LAYERS = {"VK_LAYER_KHRONOS_validation"};

std::string SimpleBasicApplication::DebugIndent = START_INDENT_SYMBOL;

#ifdef DEBUG
const bool ENABLE_VALIDATION_LAYERS = true;
#else
const bool ENABLE_VALIDATION_LAYERS = false;
#endif

static auto create_debug_utils_messenger_ext(VkInstance instance,
											 const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
											 const VkAllocationCallbacks* pAllocator,
											 VkDebugUtilsMessengerEXT* pDebugMessenger) -> VkResult {
	LOG_TRACE

	auto func =
		(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}

	return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void destroy_debug_utils_messenger_ext(VkInstance instance,
									   VkDebugUtilsMessengerEXT debugMessenger,
									   const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance,
																		   "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

VKAPI_ATTR auto VKAPI_CALL
SimpleBasicApplication::debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
									   VkDebugUtilsMessageTypeFlagsEXT message_type,
									   const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
									   void* p_user_data) -> VkBool32 {
	LOG_TRACE
	
	auto severity_str = [message_severity]() -> std::string
	{
		switch (message_severity) {
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				return "DIAGNOSTIC";
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
				return "INFO";
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				return "WARNING";
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				return "ERROR";
			default:
				return "UNKNOWN";
		}
	}();

	auto type_str = [message_type]() -> std::string
	{
		switch (message_type) {
			case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
				return "GENERAL";
			case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
				return "VALIDATION";
			case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
				return "PERFORMANCE";
			default:
				return "UNKNOWN";
		}
	}();

	auto color = [message_severity]() -> std::string
	{
		switch (message_severity) {
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				return CYAN_COLOR;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
				return GREEN_COLOR;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				return YELLOW_COLOR;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				return RED_COLOR;
			default:
				return GREY_COLOR;
		}
	}();

	std::cerr << color << "::VK " << severity_str << "::  " << "[" << type_str << "] "
			  << "validation layer: " << p_callback_data->pMessage << RESET << "\n";

	return VK_FALSE;
}

auto SimpleBasicApplication::check_validation_layer_support() -> bool {
	LOG_TRACE
	
	uint32_t layer_count;
	vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

	std::vector<VkLayerProperties> available_layers(layer_count);
	vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

	for (const char* layer_name : VALIDATION_LAYERS) {
		bool layer_found = false;

		for (const auto& layer_properties : available_layers) {
			if (strcmp(layer_name, layer_properties.layerName) == 0) {
				layer_found = true;
				break;
			}
		}

		if (!layer_found) {
			return false;
		}
	}

	return true;
}

auto SimpleBasicApplication::get_required_extensions() -> std::vector<const char*> {
	LOG_TRACE
	
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (ENABLE_VALIDATION_LAYERS) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

void SimpleBasicApplication::populate_debug_messenger_create_info(
	VkDebugUtilsMessengerCreateInfoEXT& create_info) {
	LOG_TRACE
	
	create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
		| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
		| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	create_info.pfnUserCallback = debug_callback;
}

void SimpleBasicApplication::run() {
	LOG_TRACE
	
	init_window();
	init_vulkan();
	main_loop();
	cleanup();
}

void SimpleBasicApplication::init_window() {
	LOG_TRACE
	
	init_glfw();
	window = create_window(WIDTH, HEIGHT, TITLE);
}

void SimpleBasicApplication::init_vulkan() {
	LOG_TRACE
	
	create_instance();
	setup_debug_callback();
}

void SimpleBasicApplication::setup_debug_callback() {
	LOG_TRACE
	
	if (!ENABLE_VALIDATION_LAYERS) {
		return;
	}

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populate_debug_messenger_create_info(createInfo);

	if (create_debug_utils_messenger_ext(instance, &createInfo, nullptr, &debug_messenger) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger!");
	}
}

void SimpleBasicApplication::create_instance() {
	LOG_TRACE
	
	// A Instance is a link between your Vulkan program and the library, and to create it, you will need to
	// provide the driver with some data about your program.
	if (ENABLE_VALIDATION_LAYERS && !check_validation_layer_support()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo app_info {};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = TITLE;
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "No Engine";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_4;

	VkInstanceCreateInfo create_info {};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;

	if (ENABLE_VALIDATION_LAYERS) {
		create_info.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
		create_info.ppEnabledLayerNames = VALIDATION_LAYERS.data();
	} else {
		create_info.enabledLayerCount = 0;
	}

	auto extensions = get_required_extensions();
	create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	create_info.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
	if (ENABLE_VALIDATION_LAYERS) {
		create_info.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
		create_info.ppEnabledLayerNames = VALIDATION_LAYERS.data();

		populate_debug_messenger_create_info(debug_create_info);
		create_info.pNext = (&debug_create_info);
	} else {
		create_info.enabledLayerCount = 0;

		create_info.pNext = nullptr;
	}

	if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create instance!");
	}
}

void SimpleBasicApplication::main_loop() {
	LOG_TRACE
	
	poll_events_if_window_open(window, WIDTH, HEIGHT);
}

void SimpleBasicApplication::cleanup() {
	LOG_TRACE
	
	if (ENABLE_VALIDATION_LAYERS) {
		destroy_debug_utils_messenger_ext(instance, debug_messenger, nullptr);
	}

	vkDestroyInstance(instance, nullptr);

	terminate_window(window);
}

auto open_application(SimpleBasicApplication* application) -> int {
	LOG_TRACE
	
	try {
		application->run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
