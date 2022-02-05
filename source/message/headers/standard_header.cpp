#include <http/message/headers/standard_header.hpp>

http::message::header::standard::standard(status_code std_code, string_type std_msg, version std_ver) : __M_std_status		  (std_code),
																										__M_std_status_message(std_msg) ,
																										__M_std_http_version  (std_ver) {  }

bool http::message::header::standard::operator==(status_code std_code)
{
	return __M_std_status == std_code;
}

bool http::message::header::standard::operator==(string_type std_msg)
{
	return __M_std_status_message == std_msg;
}

http::message::header::standard::status_code http::message::header::standard::code()
{
	return __M_std_status;
}

http::message::header::standard::string_type http::message::header::standard::message()
{
	return __M_std_status_message;
}