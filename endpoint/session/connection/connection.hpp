#pragma once
#include <http/endpoint/session/session.hpp>

namespace http	   {
namespace endpoint {

	class http::endpoint::session::connection
	{
	private:
		typedef SOCKET		socket_type;
		typedef sockaddr_in address_type;
		friend class http::endpoint::session::secured_connection;
	
	public:
		class   accept;
		class   sender;
		class   receiver;

	public:
		static void				   initialize();
	public:
		static session::connection from_url    (std::string url);
		static session::connection from_session(session&);
	private:
		static session::connection from_socket (socket_type, address_type);

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

void http::endpoint::session::connection::initialize()
{
	WSADATA init_ret;
	int		init_res = WSAStartup(MAKEWORD(2, 2), &init_ret);

	HTTP_EXCEPTION_THROW(init_res != 0, http::exception::session_exception("Failed to Initialize WinSock2."));
}

http::endpoint::session::connection http::endpoint::session::connection::from_url(std::string url)
{
	http::endpoint::session::connection resolv_conn;
	DNS_RECORD*							resolv_rec ;
	DNS_STATUS							resolv_res = DnsQuery_A(url.c_str(), 
				 												DNS_TYPE_A,
																DNS_QUERY_STANDARD, NULL, &resolv_rec, NULL);
	
	resolv_conn.__m_conn_socket					 = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	resolv_conn.__m_conn_address.sin_addr.s_addr =   htonl (resolv_rec->Data.A.IpAddress);
	resolv_conn.__m_conn_address.sin_port		 =   htons (80);
	resolv_conn.__m_conn_address.sin_family		 =   AF_INET;

	DnsRecordListFree		(resolv_rec, DnsFreeRecordList);
	int conn_res = ::connect(resolv_conn.__m_conn_socket, (const sockaddr*)&resolv_conn.__m_conn_address, sizeof(sockaddr_in));

	HTTP_EXCEPTION_THROW(conn_res != 0, http::exception::session_exception("Failed to Connect to Resolved Address."));
	return				 resolv_conn;
}

http::endpoint::session::connection http::endpoint::session::connection::from_session(session& __pa_session)
{
	http::endpoint::session::connection res_conn;
	res_conn.__m_conn_address = __pa_session.__m_session_address;
	res_conn.__m_conn_socket  = __pa_session.__m_session_socket;
	
	return     res_conn;
}

http::endpoint::session::connection http::endpoint::session::connection::from_socket(socket_type __pa_sock, address_type __pa_addr)
{
	http::endpoint::session::connection res_conn;
	res_conn.__m_conn_address = __pa_addr;
	res_conn.__m_conn_socket  = __pa_sock;

	return res_conn;
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
	std::size_t rcv_size = ::recv(__m_rcv_socket, (char*)&__pa_context, sizeof(ObjectType), 0);
	HTTP_EXCEPTION_THROW		 (rcv_size != sizeof(ObjectType), http::exception::session_exception("Failed to Receive."));
}

http::endpoint::session::connection::receiver& http::endpoint::session::connection::receiver::operator >> (std::pair<char*, std::size_t>&& __pa_context)
{
	std::size_t rcv_size = ::recv(__m_rcv_socket,
								 (char*)__pa_context.first,
										__pa_context.second, 0);
	HTTP_EXCEPTION_THROW   (rcv_size != __pa_context.second, http::exception::session_exception("Failed to Receive."));
}