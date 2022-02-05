#pragma once
#include <WinSock2.h>
#include <WinDNS.h>

#include <string>
#include <vector>
#include <fstream>

#include <json/json.h>

namespace http::endpoint::resolv {
	extern IP4_ADDRESS default_resolver;
	class  v4_backend
	{
	public:
		typedef std::string host_type;
		typedef sockaddr_in addr_type;
		
		typedef std::vector<host_type> canonical_result;
		typedef std::vector<addr_type> address_result  ;
		typedef std::uint16_t		   count_result	   ;

	public:
		v4_backend (std::string);
		~v4_backend();

		count_result resolve(host_type, address_result  &);
		count_result resolve(host_type, canonical_result&);

	private:
		typedef Json::Value				conf_entity;
		typedef std::ifstream			conf_stream;
		typedef Json::CharReaderBuilder conf_reader;

		conf_entity __M_v4_conf;
		conf_stream __M_v4_conf_fstream;
		conf_reader __M_v4_conf_reader ;
	};
}