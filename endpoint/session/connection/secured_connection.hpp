#pragma once
#include <http/endpoint/session/session.hpp>
#include <http/endpoint/session/connection/connection.hpp>
#include <WinDNS.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


namespace http    {
namespace endpoint{

	class session::secured_connection
	{
	public:
		typedef SSL_METHOD  ssl_method;
		typedef SSL_CTX     ssl_context;
		typedef SSL		    ssl_entity;

		typedef SOCKET		socket_type;
		typedef sockaddr_in address_type;

	public:
		class sender;
		class receiver;

	private:
		static session::secured_connection from_socket(socket_type, address_type);
	public:
		static session::secured_connection from_url	  (std::string);

	private:
		ssl_method  * __m_ssl_method ;
		ssl_context * __m_ssl_context;
		ssl_entity  * __m_ssl_entity ;

		socket_type  __m_ssl_socket;
		address_type __m_ssl_address;
	};

	class session::secured_connection::sender
	{
	private:
		sender(ssl_entity* __pa_ssl) : __m_ssl_entity(__pa_ssl) {  }
	public:
		static secured_connection::sender from_connection(session::secured_connection& __pa_conn) { return sender(__pa_conn.__m_ssl_entity); }

		template <typename ObjectType>
		secured_connection::sender& operator << (ObjectType&);
		secured_connection::sender& operator << (std::pair<char*, std::size_t>&&);

	private:
		ssl_entity* __m_ssl_entity;
	};

	class session::secured_connection::receiver
	{
	private:
		receiver(ssl_entity* __pa_ssl) : __m_ssl_entity(__pa_ssl) {  }
	public:
		static secured_connection::receiver from_connection(session::secured_connection& __pa_conn) { return receiver(__pa_conn.__m_ssl_entity); }

		template <typename ObjectType>
		secured_connection::receiver& operator >> (ObjectType&);
		secured_connection::receiver& operator >> (std::pair<char*, std::size_t>&&);

	private:
		ssl_entity* __m_ssl_entity;
	};
}
}
http::endpoint::session::secured_connection http::endpoint::session::secured_connection::from_socket(socket_type __pa_sock, address_type __pa_addr)
{
	http::endpoint::session::secured_connection sec_conn;
	
	SSL_load_error_strings   ();
	SSLeay_add_ssl_algorithms();

	sec_conn.__m_ssl_method  = (ssl_method*)TLSv1_2_client_method();
	sec_conn.__m_ssl_context =				SSL_CTX_new(sec_conn.__m_ssl_method);
	sec_conn.__m_ssl_entity  =				SSL_new    (sec_conn.__m_ssl_context);
	
	HTTP_EXCEPTION_THROW(SSL_set_fd (sec_conn.__m_ssl_entity, __pa_sock) != 1, http::exception::session_exception("Failed to Bind SSL Socket to Entity."));
	HTTP_EXCEPTION_THROW(SSL_connect(sec_conn.__m_ssl_entity)			 != 1, http::exception::session_exception("Failed to Connect SSL Session."));

	sec_conn.__m_ssl_socket  = __pa_sock;
	sec_conn.__m_ssl_address = __pa_addr;

	return sec_conn;
}

http::endpoint::session::secured_connection http::endpoint::session::secured_connection::from_url(std::string __pa_url)
{
	DNS_RECORD* resolv_rec;
	DNS_STATUS  resolv_res = DnsQuery_A(__pa_url.c_str(),
										DNS_TYPE_A,
										DNS_QUERY_STANDARD, NULL, &resolv_rec, NULL);

	socket_type  resolv_conn = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	address_type resolv_addr;

	resolv_addr.sin_addr.s_addr = resolv_rec->Data.A.IpAddress;
	resolv_addr.sin_port		= htons(HTTP_SECURE_CONN_PORT);
	resolv_addr.sin_family		= AF_INET;

	HTTP_DEBUG_PRINT("[SecureConn] SSL Address :: "s + std::string(::inet_ntoa(resolv_addr.sin_addr)));

	int resolv_conn_res = connect(resolv_conn, (const sockaddr*)&resolv_addr, sizeof(sockaddr_in));
	HTTP_EXCEPTION_THROW	     (resolv_conn_res != 0, http::exception::session_exception("Failed to Connect to SSL Port."));

	HTTP_DEBUG_PRINT("[SecureConn] SSL Session :: Connected Successfully.");
	HTTP_DEBUG_PRINT("[SecureConn] SSL Connected to :: "s + std::string(::inet_ntoa(resolv_addr.sin_addr)));

	return from_socket(resolv_conn, resolv_addr);
}

template <typename ObjectType>
http::endpoint::session::secured_connection::sender& http::endpoint::session::secured_connection::sender::operator << (ObjectType& __pa_context)
{
	int					 snd_size  = ::SSL_write(__m_ssl_entity, (const char*)&__pa_context, sizeof(ObjectType));
	HTTP_EXCEPTION_THROW(snd_size <= 0, http::exception::session_exception("Failed to Send to SSL Stream."));
}

http::endpoint::session::secured_connection::sender& http::endpoint::session::secured_connection::sender::operator << (std::pair<char*, std::size_t>&& __pa_context)
{
	int					 snd_size  = ::SSL_write(__m_ssl_entity, (const char*)__pa_context.first, __pa_context.second);
	HTTP_EXCEPTION_THROW(snd_size <= 0, http::exception::session_exception("Failed to Send to SSL Stream."));
}

template <typename ObjectType>
http::endpoint::session::secured_connection::receiver& http::endpoint::session::secured_connection::receiver::operator >> (ObjectType& __pa_context)
{
	int					 rcv_size  = ::SSL_read(__m_ssl_entity, (char*)&__pa_context, sizeof(ObjectType), 0);
	HTTP_EXCEPTION_THROW(rcv_size <= 0, http::exception::session_exception("Failed to Receive from SSL Stream."));
}

http::endpoint::session::secured_connection::receiver& http::endpoint::session::secured_connection::receiver::operator >> (std::pair<char*, std::size_t>&& __pa_context)
{
	int					 rcv_size  = ::SSL_read(__m_ssl_entity, (char*)__pa_context.first, __pa_context.second);
	HTTP_EXCEPTION_THROW(rcv_size <= 0, http::exception::session_exception("Failed to Receive from SSL Stream."));
}