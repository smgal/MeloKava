
#include "os_utils.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <cassert>

///////////////////////////////////////////////////////////////////////////////
// common

namespace
{
	#define _COMPOSE_VAR_PARAM(result) \
	{ \
		char s_var[1024]; \
		va_list args; \
		va_start(args, fmt); \
		vsprintf(s_var, fmt, args); \
		va_end(args); \
		result += s_var; \
	}

	std::string _composeString(char category, const std::string& tag, const std::string& message)
	{
		char sz_category[] = "[?]";
		sz_category[1] = category;

		std::string result;
		result += sz_category;
		result += "[";
		result += tag;
		result += "] ";
		result += message;
		result += "\n";

		return result;
	}
}

void os::log::e(std::string tag, const char* fmt, ...)
{
	std::string message;
	_COMPOSE_VAR_PARAM(message);
	std::string s = _composeString('E', tag, message);

	os::print(s);
}

void os::log::i(std::string tag, const char* fmt, ...)
{
	std::string message;
	_COMPOSE_VAR_PARAM(message);
	std::string s = _composeString('I', tag, message);

	os::print(s);
}

void os::log::d(std::string tag, const char* fmt, ...)
{
	std::string message;
	_COMPOSE_VAR_PARAM(message);
	std::string s = _composeString('D', tag, message);

	os::print(s);
}

///////////////////////////////////////////////////////////////////////////////
// implementation

#if _WIN32

#include <windows.h>

void os::print(std::string s)
{
	OutputDebugStringA(s.c_str());
}

#elif __APPLE__

#include <stdlib.h>

void os::print(std::string s)
{
	printf("%s", s.c_str());
}

#elif __ANDROID__

#include <android/log.h>

void os::print(std::string s)
{
	__android_log_print(ANDROID_LOG_DEBUG, "HumOn", "%s", s.c_str());
}

#elif __LINUX__

#include <stdio.h>

void os::print(std::string s)
{
	printf("%s", s.c_str());
}

#else
#	error "OS not determined"

#endif
