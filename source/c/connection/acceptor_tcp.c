#include <http/connection/acceptor/acceptor_tcp.h>
#include <http/connection/details/acceptor/http_acceptor_tcp.h>

synapse_http_connection_acceptor_tcp_handle
synapse_http_connection_acceptor_tcp_initialize_from_v4(synapse_http_connection_addr_v4 pV4)
{
	synapse_http_connection_acceptor_tcp_handle ptr_handle
		= { .opaque = __synapse_http_connection_acceptor_tcp_initialize_from_v4(pV4) };

	return ptr_handle;
}

synapse_http_connection_acceptor_tcp_handle
synapse_http_connection_acceptor_tcp_initialize_from_v6(synapse_http_connection_addr_v6 pV6)
{
	synapse_http_connection_acceptor_tcp_handle ptr_handle
		= { .opaque = __synapse_http_connection_acceptor_tcp_initialize_from_v6(pV6) };

	return ptr_handle;
}

void
synapse_http_connection_acceptor_tcp_bind_v4(synapse_http_connection_acceptor_tcp_handle pHandle)
{
	__synapse_http_connection_acceptor_tcp_bind_v4(pHandle.opaque);
}

void
synapse_http_connection_acceptor_tcp_listen(synapse_http_connection_acceptor_tcp_handle pHandle, int pBacklog)
{
	__synapse_http_connection_acceptor_tcp_listen(pHandle.opaque, pBacklog);
}

synapse_http_connection_handle
synapse_http_connection_acceptor_tcp_accept(synapse_http_connection_acceptor_tcp_handle pHandle)
{
	synapse_http_connection_handle ptr_handle
		= { .opaque = __synapse_http_connection_acceptor_tcp_accept(pHandle.opaque) };

	return ptr_handle;
}