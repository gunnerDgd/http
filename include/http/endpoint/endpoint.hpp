#pragma once
#include <string>

namespace http::endpoint {
	class url
	{
		friend class v4_resolv;
		friend class v6_resolv;
	public:
		typedef std::string string_type;
	public:
		url (string_type&);
		~url()			  {  }

	public:
		bool operator==(url&);
		bool operator!=(url&);

	private:
		string_type __M_url_address;
	};
}

http::endpoint::url::url(string_type& url_string) : __M_url_address(url_string)
{
	auto url_proto = __M_url_address.find("://"); // Find Prefix.
}

bool http::endpoint::url::operator==(url& url_compare)
{
	return (__M_url_address == url_compare.__M_url_address);
}

bool http::endpoint::url::operator!=(url& url_compare)
{
	return !(__M_url_address == url_compare.__M_url_address);
}