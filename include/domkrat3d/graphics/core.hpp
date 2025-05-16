#pragma once

#include <GLFW/glfw3.h>

namespace graphics_core {
	/**
	 * @brief Initialize GLFW
	 *
	 * @param resizable window resizable status
	 **/
	void initializing_glfw(bool resizable = false);

	/**
	 * @brief Create a GLFW window object
	 *
	 * @param width window width
	 * @param height window height
	 * @param title window title
	 * @param fullscreen window fullscreen status (default false)
	 * @return GLFWwindow* GLFW Window Object or nullptr
	 **/
	auto create_window(int width, int height, const char* title, bool fullscreen = false) -> GLFWwindow*;

	/**
	 * @brief Setup GLEW
	 *
	 * @return int status code
	 **/
	auto setup_glew() -> int;

	/**
	 * @brief Terminate window
	 * 
	 * @param window window object
	 * @param terminate terminate glfw status (default false)
	 **/
	void terminate_window(GLFWwindow* window, bool terminate = false);

	/**
	 * @brief Mainloop of OpenGL
	 *
	 * @param window GLFW Window
	 * @param width frame buffer width
	 * @param height frame buffer height
	 * @return int status code
	 **/
	auto mainloop(GLFWwindow* window, int width, int height) -> int;
}	 // namespace graphics_core

/**
 * @brief Create a simple window
 **/
void create_simple_window();
