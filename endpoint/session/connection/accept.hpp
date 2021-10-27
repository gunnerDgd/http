#pragma once
#include <http/endpoint/session/connection/connection.hpp>

namespace http	   {
namespace endpoint {

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