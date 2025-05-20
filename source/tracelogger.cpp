#include <iostream>

#define GLEW_STATIC
#include <GL/gl.h>

#define GLFW_DLL

#include "domkrat3d/tracelogger.hpp"

std::string TraceLogger::Indent = "";

TraceLogger::TraceLogger(const char* filename, const char* funcname, int linenumber)
	: m_FILENAME(filename)
	, m_FUNCNAME(funcname) {
	std::cout << "::Trace::  " << Indent << "Entering " << m_FUNCNAME << "() - (" << m_FILENAME << ":"
			  << linenumber << ")" << '\n';
	if (Indent.length() == 0) {
		Indent.append(START_INDENT_SYMBOL);
	} else {
		Indent.append(INDENT_SYMBOL);
	}
}

TraceLogger::~TraceLogger() {
	Indent.resize(Indent.length() - INDENT_LENGTH);
	std::cout << "::Trace::  " << Indent << "Leaving " << m_FUNCNAME << "() - (" << m_FILENAME << ")"
			  << '\n';
}

void APIENTRY callback(GLenum source,
					   GLenum type,
					   GLuint id,
					   GLenum severity,
					   GLsizei length,
					   const GLchar* message,
					   const void* userParam) {
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) {
		return;
	}

	auto source_str = [source]() -> std::string
	{
		switch (source) {
			case GL_DEBUG_SOURCE_API:
				return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION:
				return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER:
				return "OTHER";
			default:
				return "UNKNOWN";
		}
	}();

	const auto* type_str = [type]()
	{
		switch (type) {
			case GL_DEBUG_TYPE_ERROR:
				return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				return "DEPRECATED_BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				return "UNDEFINED_BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY:
				return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE:
				return "PERFORMANCE";
			case GL_DEBUG_TYPE_MARKER:
				return "MARKER";
			case GL_DEBUG_TYPE_OTHER:
				return "OTHER";
			default:
				return "UNKNOWN";
		}
	}();

	const auto* severity_str = [severity]()
	{
		switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				return "NOTIFICATION";
			case GL_DEBUG_SEVERITY_LOW:
				return "LOW";
			case GL_DEBUG_SEVERITY_MEDIUM:
				return "MEDIUM";
			case GL_DEBUG_SEVERITY_HIGH:
				return "HIGH";
			default:
				return "UNKNOWN";
		}
	}();

	std::cout << "::GL DEBUG::	" << source_str << ", " << type_str << ", " << severity_str << ", " << id
			  << ": " << message << "\n";
}
