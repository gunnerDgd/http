#pragma once
#include <WinSock2.h>
#include <WinDNS.h>

#include <string>
#include <future>
#include <unordered_map>

#include <http/types/define.hpp>
#include <http/types/exception.hpp>

namespace http	   {
namespace endpoint {

	class session
	{
	public:
		class cookie;
		class connection;
		
	private:
		SOCKET	    __m_session_socket;

		sockaddr_in __m_session_address;
		std::string __m_session_key;
	};

	class session::cookie 
	{
	public:
		typedef std::string							   key_type;
		typedef std::unordered_map<key_type, key_type> cookie_set;

		key_type operator[]			  (key_type);
		void	 add_session_cookie   (key_type, key_type);
		void	 delete_session_cookie(key_type);

	private:
		cookie_set __m_session_cookie;
		key_type   __m_session_key;
	};
}
}



http::endpoint::session::cookie::key_type http::endpoint::session::cookie::operator[](key_type __pa_key)
{
	return (__m_session_cookie.find(__pa_key) != __m_session_cookie.end())
		? __m_session_cookie[__pa_key]
		: std::string("");
}

void http::endpoint::session::cookie::add_session_cookie(key_type __pa_key, key_type __pa_value)
{
	__m_session_cookie.insert({ __pa_key, __pa_value });
}

void http::endpoint::session::cookie::delete_session_cookie(key_type __pa_key)
{
	__m_session_cookie.erase(__pa_key);
}

