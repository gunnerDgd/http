#pragma once
#include <type_traits>
#include <http/message/raw.hpp>

namespace http::stream {
	template <typename ReaderType, typename ReaderBackend>
	class basic_reader
	{
	public:
		typedef ReaderType    reader_type;
		typedef ReaderBackend backend_type;

		typedef typename ReaderBackend::pointer_type pointer_type;
		typedef typename ReaderBackend::size_type    size_type;

	public:
		basic_reader (ReaderBackend&);
		~basic_reader();

	public:
		reader_type read_from() requires std::is_constructible_v<ReaderType, pointer_type, size_type>;
	};
}