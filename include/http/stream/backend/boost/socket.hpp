#pragma once
#include <boost/asio.hpp>
#include <string>

namespace http::stream::backend {
	class boost_socket
	{
	public:
		typedef boost::asio::ip::tcp::socket   socket_type ;
		typedef boost::asio::ip::tcp::endpoint address_type;
		typedef boost::asio::io_context		   async_handle;

		typedef std::string					   host_address_type;
		typedef std::uint16_t				   host_port_type;

		typedef std::size_t					   size_type;
		typedef std::uint8_t*				   pointer_type;

	public:
		boost_socket (socket_type&, address_type&);
		boost_socket (async_handle&, host_address_type, host_port_type);
		~boost_socket();

	public:
		bool connect   ();
		bool disconnect();

	public:
		size_type read (pointer_type, size_type);
		size_type write(pointer_type, size_type);

	private:
		socket_type   __M_backend_socket ;
		address_type  __M_backend_address;
		async_handle& __M_backend_async  ;
	};
}

