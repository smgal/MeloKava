
#ifndef __OS_UTIL_H__
#define __OS_UTIL_H__

#if defined(_MSC_VER)
#pragma warning(disable: 4996)
#endif

#include <string>
#include <sstream>

namespace os
{
	void print(std::string s);

	class log
	{
	public:
		static void e(std::string tag, const char* fmt, ...);
		static void i(std::string tag, const char* fmt, ...);
		static void d(std::string tag, const char* fmt, ...);
	};
}

template <typename T>
std::string TO_STRING(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

#endif // #ifndef __OS_UTIL_H__
