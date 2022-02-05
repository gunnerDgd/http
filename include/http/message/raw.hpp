#pragma once
#include <string_tools/split/split.hpp>

namespace http::message {
	template <typename AllocBackend = void>
	class raw;

	template <>
	class raw<void>
	{
		typedef std::uint8_t* pointer_type ;
		typedef std::size_t   size_type    ;
		typedef void	      alloc_backend;

		raw (pointer_type, size_type);
	public:
		~raw();

	private:
		pointer_type __M_raw_pointer;
		size_type    __M_raw_size;
	};
}