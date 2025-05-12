#pragma once

#include <string>

#include "domkrat3d/_default.hpp"

#ifdef DEBUG
#define LOG_TRACE TraceLogger logger(__FILE__, __FUNCTION__, __LINE__);
#else
#define LOG_TRACE
#endif

class TraceLogger {
    public:
        static std::string Indent;

        TraceLogger(const char* FILENAME, const char* FUNCNAME, int linenumber);
        ~TraceLogger();
        
    private:
        const char* m_FILENAME;
        const char* m_FUNCNAME;
};
