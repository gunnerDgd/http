#pragma once
#include <cstddef>

namespace http    {
	class message
	{
	public:
		class response;
		class request ;

	public:
		message(char* __pa_msg, std::size_t __pa_size)
			: raw_message(__pa_msg),
		 	  raw_size   (__pa_size) { }

		~message() { delete[] raw_message; }

	public:
		char*		get_raw_pointer() { return raw_message; }
		std::size_t get_raw_size   () { return raw_size   ; }

	protected:
		char*		raw_message;
		std::size_t raw_size;
	};
}