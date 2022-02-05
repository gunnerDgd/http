#pragma once
#include <string>

namespace http		{
namespace exception {

	class general_exception
	{
	protected:
		std::string __m_excp_msg;

	public:
		general_exception		 (std::string __pa_str) : __m_excp_msg(__pa_str) { }
		std::string error_message()												 { return __m_excp_msg; }
	};

	class parse_exception : public general_exception
	{
	public:
		parse_exception(std::string __pa_excp) : general_exception("[PARSE ERROR] :: " + __pa_excp ) { }
	};
	
	class session_exception : public general_exception
	{
	public:
		session_exception(std::string __pa_excp) : general_exception("[SESSION ERROR] :: " + __pa_excp) { }
	};

	class resource_exception : public general_exception
	{
	public:
		resource_exception(std::string __pa_excp) : general_exception("[RESOURCE ERROR] :: " + __pa_excp) { }
	};
}
}
