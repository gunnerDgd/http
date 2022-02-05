#include <http/stream/backend/boost/socket.hpp>

http::stream::backend::boost_socket::boost_socket(async_handle& async, host_address_type addr, host_port_type port) 
	: __M_backend_async  (async),
	  __M_backend_address(boost::asio::ip::address_v4::from_string(addr), port),
	  __M_backend_socket (__M_backend_async)								   {  }

http::stream::backend::boost_socket::~boost_socket()
{

}