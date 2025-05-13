#pragma once

#include <string>

#include "domkrat3d/_default.hpp"

#ifdef DEBUG
#	 define LOG_TRACE TraceLogger logger(__FILE__, __FUNCTION__, __LINE__);
#else
#	 define LOG_TRACE
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
