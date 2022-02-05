#pragma once
#include <string>

namespace http::messages::header {
	class connection
	{
	public:
		typedef std::string string_type;
		enum class			connection_type { close, keep_alive };
		
		connection(string_type, connection_type);

	private:
		string_type		__M_conn_srv_name;
		connection_type __M_conn_type;
	};
}