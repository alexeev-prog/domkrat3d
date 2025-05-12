#include <iostream>
#include "domkrat3d/tracelogger.hpp"

std::string TraceLogger::Indent;

TraceLogger::TraceLogger(const char* filename, const char* funcname, int linenumber) : m_FILENAME(filename), m_FUNCNAME(funcname) {
	std::cout << "::Trace::    " << Indent << "Entering " << m_FUNCNAME << "() - (" << m_FILENAME << ":" << linenumber << ")" << '\n';
	if (Indent.length() == 0) {
		Indent.append(START_INDENT_SYMBOL);
	} else {
		Indent.append(INDENT_SYMBOL);
	}
}

TraceLogger::~TraceLogger() {
	Indent.resize(Indent.length() - INDENT_LENGTH);
	std::cout << "::Trace::    " << Indent << "Leaving " << m_FUNCNAME << "() - (" << m_FILENAME << ")" << '\n';
}
