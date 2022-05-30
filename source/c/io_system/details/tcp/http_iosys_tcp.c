#include <http/io_system/details/tcp/http_iosys_tcp.h>

synapse_http_io_system
__synapse_http_io_system_tcp_initialize(__synapse_http_connection_handle_tcp pTcp)
{
	synapse_http_io_system ptr_iosys = 
	{
		.read_from = &__synapse_http_io_system_tcp_read_from,
		.write_to  = &__synapse_http_io_system_tcp_write_to ,
		.io_entity = &pTcp
	};

	return ptr_iosys;
}

void
__synapse_http_io_system_tcp_cleanup(synapse_http_io_system pIosys)
{
	
}

size_t __synapse_http_io_system_tcp_read_from(void* pTcp, void* pReadBuffer, size_t pReadSize)
{
	return recv(((__synapse_http_connection_handle_tcp*)pTcp)->conn_handle, 
														pReadBuffer		  , 
														pReadSize, 0);
}
size_t __synapse_http_io_system_tcp_write_to(void* pTcp, void* pWriteBuffer, size_t pWriteSize)
{
	return send(((__synapse_http_connection_handle_tcp*)pTcp)->conn_handle, 
														pWriteBuffer	  , 
														pWriteSize, 0);
}