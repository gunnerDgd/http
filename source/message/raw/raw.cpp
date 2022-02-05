#include <http/message/raw.hpp>

http::message::raw<void>::raw(pointer_type ptr, size_type size) : __M_raw_pointer(ptr),
																  __M_raw_size   (size) { }

http::message::raw<void>::~raw()
{
	delete[] __M_raw_pointer;
}