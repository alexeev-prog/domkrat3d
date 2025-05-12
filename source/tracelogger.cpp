#include <iostream>
#include "domkrat3d/tracelogger.hpp"

std::string TraceLogger::Indent;

TraceLogger::TraceLogger(const char* FILENAME, const char* FUNCNAME, int linenumber) : m_FILENAME(FILENAME), m_FUNCNAME(FUNCNAME) {
	std::cout << "Trace::  " << Indent << "Entering " << m_FUNCNAME << "() - (" << m_FILENAME << ":" << linenumber << ")" << '\n';
	Indent.append("  ");
}

TraceLogger::~TraceLogger() {
	Indent.resize(Indent.length() - 2);
	std::cout << "Trace::  " << Indent << "Leaving  " << m_FUNCNAME << "() - (" << m_FILENAME << ")" << '\n';
}
