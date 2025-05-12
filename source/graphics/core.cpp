#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_DLL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW/glfw3.h>

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 6

#include "domkrat3d/graphics/core.hpp"
#include "domkrat3d/tracelogger.hpp"

namespace graphics_core {
	void initializing_glfw(bool resizable) {
		LOG_TRACE
		
		std::cout << "Starting initializing OpenGL " << OPENGL_MAJOR_VERSION << "." << OPENGL_MINOR_VERSION
				  << "\n";
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		if (resizable) {
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		} else {
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}
	}

	auto create_window(int width, int height, const char* title) -> GLFWwindow* {
		LOG_TRACE

		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr) {
			std::cerr << "Failed to create GLFW Window\n";
			glfwTerminate();
			return nullptr;
		}

		glfwMakeContextCurrent(window);

		return window;
	}

	auto setup_glew() -> int {
		LOG_TRACE

		glewExperimental = GL_TRUE;
		// Initialize GLEW to setup the OpenGL Function pointers
		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialize GLEW\n";
			return -1;
		}

		return 0;
	}

	auto mainloop(GLFWwindow* window, int width, int height) -> int {
		LOG_TRACE

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		while (glfwWindowShouldClose(window) == 0) {
			glfwPollEvents();

			// Render Color
			glClearColor(0.0F, 0.0F, 0.3F, 1.0F);
			glClear(GL_COLOR_BUFFER_BIT);

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}

		// Terminate GLFW, clearing any resources allocated by GLFW.
		glfwTerminate();
		return 0;
	}
}	 // namespace graphics_core

void create_simple_window() {
	LOG_TRACE
	
	const int WIDTH = 800;
	const int HEIGHT = 600;

	graphics_core::initializing_glfw();
	GLFWwindow* window = graphics_core::create_window(WIDTH, HEIGHT, "Domkrat3D Example");

	graphics_core::setup_glew();

	int status_code = graphics_core::mainloop(window, WIDTH, HEIGHT);

	std::cout << "mainloop() status code: " << status_code << "\n";
}
