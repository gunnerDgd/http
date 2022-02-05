#pragma once
#include <WinSock2.h>
#include <WinDNS.h>

#include <string>
#include <future>
#include <unordered_map>

#include <http/resource/resource.hpp>
#include <http/message/message.hpp>
#include <http/types/define.hpp>

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

	class session::connection
	{
	private:
		typedef SOCKET		socket_type ;
		typedef sockaddr_in address_type;
	public:
		class   accept;

	public:
		static session::connection from_socket (socket_type);
		static session::connection from_socket (socket_type, address_type&);

		static session::connection from_session(session&);

	public:
		void		  operator()(http::resource&);
		void		  operator()(http::message &);
		http::message operator()();

	private:
		socket_type			__m_conn_socket ;
		address_type		__m_conn_address;
	};

	class session::connection::accept
	{
	public:
		accept(std::string, uint16_t);

		template <typename AsyncFunc>
		void				operator()(AsyncFunc&&);
		session::connection operator()();

	private:
		sockaddr_in __m_acpt_address;
		SOCKET		__m_acpt_socket;
	};
}
}

http::endpoint::session::connection::accept::accept(std::string __pa_addr, uint16_t __pa_port)
{
	__m_acpt_address.sin_addr.s_addr = ::inet_addr(__pa_addr.c_str());
	__m_acpt_address.sin_port		 =   htons(__pa_port);
	__m_acpt_address.sin_family		 =   AF_INET;
	__m_acpt_socket					 = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	HTTP_EXCEPTION_THROW(::bind(__m_acpt_socket, (const sockaddr*)&__m_acpt_address, sizeof(sockaddr_in)) != 0,
						 http::exception::session_exception("Failed to Bind Socket."));

	HTTP_EXCEPTION_THROW(::listen(__m_acpt_socket, 20) != 0,
						 http::exception::session_exception("Failed to Listen to New Connection."));
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

template <typename AsyncFunc>
void http::endpoint::session::connection::accept::operator()(AsyncFunc&& __pa_async)
{
	std::async([this]() { __pa_async(this->operator()()); });
}

http::endpoint::session::connection http::endpoint::session::connection::accept::operator()()
{
	SOCKET		acpt_socket;
	sockaddr_in acpt_address;
	int			acpt_address_size = sizeof(acpt_address);

	HTTP_EXCEPTION_THROW((acpt_socket = ::accept(__m_acpt_socket, (sockaddr*)&acpt_address, &acpt_address_size)) == INVALID_SOCKET,
						  http::exception::session_exception("Failed to Accept New Connection."));

	return connection::from_socket(acpt_socket, acpt_address);
}

http::endpoint::session::connection http::endpoint::session::connection::from_socket(socket_type __pa_socket)
{
	session::connection res_conn;
	int					res_addr_size = sizeof(sockaddr_in);
	
	getsockname(__pa_socket, (sockaddr*)&res_conn.__m_conn_address, &res_addr_size);
	return		res_conn;
}

http::endpoint::session::connection http::endpoint::session::connection::from_socket(socket_type __pa_sock, address_type& __pa_addr)
{
	connection conn_new;
	conn_new.__m_conn_address = __pa_addr;
	conn_new.__m_conn_socket  = __pa_sock;

	return conn_new;
}

http::endpoint::session::connection http::endpoint::session::connection::from_session(session& __pa_session)
{
	return from_socket(__pa_session.__m_session_socket, __pa_session.__m_session_address);
}

/*
* Connection Class
* 
* :: Actual Connection with Client.
*    Stores Socket and Its Address.
* 
*/

http::message http::endpoint::session::connection::operator()()
{
	HTTP_MESSAGE_ALLOCATE(char* msg_raw_field);
	std::size_t rcv_size = ::recv(__m_conn_socket, msg_raw_field, HTTP_MESSAGE_MTU, 0);

	HTTP_EXCEPTION_THROW (rcv_size == 0, http::exception::session_exception("Failed to Receive Raw Data."));
	return								 http::message(msg_raw_field, HTTP_MESSAGE_MTU);
}

void http::endpoint::session::connection::operator()(http::message& __pa_msg)
{
	std::size_t snd_size = ::send(__m_conn_socket, 
								 (const char*)__pa_msg.get_raw_pointer(), 
											  __pa_msg.get_raw_size   (), 0);
	HTTP_EXCEPTION_THROW(snd_size != __pa_msg.get_raw_size(), http::exception::session_exception("Failed to Send"));	
}

void http::endpoint::session::connection::operator()(http::resource& __pa_res)
{
	std::size_t snd_size = ::send(__m_conn_socket,
								 (const char*)__pa_res.get_resource(),
											  __pa_res.get_size	   (), 0);
	HTTP_EXCEPTION_THROW(snd_size != __pa_res.get_size(), http::exception::session_exception("Failed to Send"));
}