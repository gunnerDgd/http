#pragma once
#include <http/endpoint/session/session.hpp>

namespace http	   {
namespace endpoint {

	class http::endpoint::session::connection
	{
	private:
		typedef SOCKET		socket_type;
		typedef sockaddr_in address_type;
	
	public:
		class   accept;
	public:
		class   sender;
		class   receiver;

	public:
		static session::connection from_socket(socket_type);
		static session::connection from_socket(socket_type, address_type&);

		static session::connection from_session(session&);

	private:
		socket_type			__m_conn_socket;
		address_type		__m_conn_address;
	};

	class session::connection::sender
	{
	private:
		sender(socket_type __pa_sock) : __m_snd_socket(__pa_sock) {  }
	public:
		static session::connection::sender from_connection(session::connection& __pa_conn) { return sender(__pa_conn.__m_conn_socket); }
		
		template <typename ObjectType>
		sender& operator << (ObjectType&);
		sender& operator << (std::pair<char*, std::size_t>&&);

	private:
		socket_type __m_snd_socket;
	};

	class session::connection::receiver
	{
	private:
		receiver(socket_type __pa_sock) : __m_rcv_socket(__pa_sock) {  }
	public:
		static session::connection::receiver from_connection(session::connection& __pa_conn) { return receiver(__pa_conn.__m_conn_socket); }

		template <typename ObjectType>
		receiver& operator >> (ObjectType&);
		receiver& operator >> (std::pair<char*, std::size_t>&&);

	private:
		socket_type __m_rcv_socket;
	};

}
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
	conn_new.__m_conn_socket = __pa_sock;

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

// Connection's Sender And Receiver
template <typename ObjectType>
http::endpoint::session::connection::sender& http::endpoint::session::connection::sender::operator << (ObjectType& __pa_context)
{
	std::size_t snd_size = ::send(__m_snd_socket, (const char*)&__pa_context, sizeof(ObjectType), 0);
	HTTP_EXCEPTION_THROW         (snd_size != sizeof(ObjectType), http::exception::session_exception("Failed to Send."));
}

http::endpoint::session::connection::sender& http::endpoint::session::connection::sender::operator << (std::pair<char*, std::size_t>&& __pa_context)
{
	std::size_t snd_size = ::send(			  __m_snd_socket	 , 
								 (const char*)__pa_context.first , 
											  __pa_context.second, 0);
	HTTP_EXCEPTION_THROW         (snd_size != __pa_context.second, http::exception::session_exception("Failed to Send."));
}

template <typename ObjectType>
http::endpoint::session::connection::receiver& http::endpoint::session::connection::receiver::operator >> (ObjectType& __pa_context)
{
	std::size_t rcv_size = ::send(__m_rcv_socket, (const char*)&__pa_context, sizeof(ObjectType), 0);
	HTTP_EXCEPTION_THROW		 (rcv_size != sizeof(ObjectType), http::exception::session_exception("Failed to Send."));
}

http::endpoint::session::connection::receiver& http::endpoint::session::connection::receiver::operator >> (std::pair<char*, std::size_t>&& __pa_context)
{
	std::size_t rcv_size = ::send(__m_rcv_socket,
								 (const char*)__pa_context.first,
											  __pa_context.second, 0);
	HTTP_EXCEPTION_THROW		 (rcv_size != __pa_context.second, http::exception::session_exception("Failed to Send."));
}