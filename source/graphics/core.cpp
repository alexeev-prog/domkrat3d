#include "domkrat3d/graphics/core.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_DLL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW/glfw3.h>

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 6

namespace graphics_core {
	void initializing_glfw(bool resizable) {
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
}
