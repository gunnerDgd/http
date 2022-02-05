#pragma once
#include <string>

namespace http::message::header {
	class standard
	{
	public:
		enum class status  : std::uint16_t;
		enum class version : std::uint8_t ;
		
		typedef std::string string_type;
		typedef status	    status_code;

	public:
		standard(status_code, string_type, version);

	public:
		status_code code   ();
		string_type message();

	public:
		bool operator==(status_code);
		bool operator==(string_type);

	private:
		status_code __M_std_status;
		string_type __M_std_status_message;
		version		__M_std_http_version;
	};

	enum class standard::version : std::uint8_t
	{
		http_1_0,
		http_1_1,
		http_2_0
	};

	enum class standard::status : std::uint16_t
	{
		continue_request    = 100,
		protocol_transition = 101,

		ok		  = 200,
		completed = 201,
		accepted  = 202,

		untrustable_content = 203,
		no_content		    = 204,
		renew_content		= 205,
		partial_completion  = 206,

		invalid_request = 400,
		unauthorized    = 401,
		forbidden	    = 403,
		not_found	    = 404,

		internal_error			 = 500,
		unsupported_feature		 = 501,
		bad_gateway				 = 502,
		unusable_service		 = 503,
		gateway_timeout			 = 504,
		unsupported_http_version = 505
	};
}