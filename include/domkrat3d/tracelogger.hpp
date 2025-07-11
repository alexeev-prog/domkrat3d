#pragma once

#include <string>

#define GLEW_STATIC
#include <GL/gl.h>

#include "domkrat3d/_default.hpp"

#ifdef DEBUG
#    define LOG_TRACE TraceLogger logger(__FILE__, __FUNCTION__, __LINE__);
#else
#    define LOG_TRACE
#endif

class TraceLogger {
    /**
     * @brief TraceLogger - use LOG_TRACE for tracing function calls
     *
     **/

  public:
    static std::string Indent;

    /**
     * @brief Construct a new Trace Logger object
     *
     * @param filename logged filename
     * @param funcname logged function name
     * @param linenumber logged line number where function called
     **/
    TraceLogger(const char* filename, const char* funcname, int linenumber);

    /**
     * @brief Destroy the Trace Logger object
     *
     **/
    ~TraceLogger();

  private:
    const char* m_FILENAME;
    const char* m_FUNCNAME;
};

/**
 * @brief GL Debug Callback function
 *
 * @param source source of message
 * @param type message type
 * @param id message id
 * @param severity message severity
 * @param length message length
 * @param message message text
 * @param userParam user param
 **/
void APIENTRY callback(GLenum source,
                       GLenum type,
                       GLuint id,
                       GLenum severity,
                       GLsizei length,
                       const GLchar* message,
                       const void* userParam);
