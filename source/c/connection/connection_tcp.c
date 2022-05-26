#include <http/connection/connection_tcp.h>
#include <http/connection/details/http_connection.h>

synapse_http_connection_handle
synapse_http_connection_tcp_initialize_from_v4(synapse_http_connection_addr_v4 pV4)
{
	synapse_http_connection_handle ptr_handle
		= { .opaque = __synapse_http_connection_tcp_initialize_from_v4(pV4) };

	return ptr_handle;
}

synapse_http_connection_handle
synapse_http_connection_tcp_initialize_from_v6(synapse_http_connection_addr_v6 pV6)
{
	synapse_http_connection_handle ptr_handle
		= { .opaque = __synapse_http_connection_tcp_initialize_from_v6(pV6) };

	return ptr_handle;
}

synapse_http_connection_handle
synapse_http_connection_tcp_initialize_v4_from_url(synapse_http_connection_addr_url pUrl)
{
	synapse_http_connection_handle ptr_handle
		= { .opaque = __synapse_http_connection_tcp_initialize_v4_from_url(pUrl) };

	return ptr_handle;
}

synapse_http_connection_handle
synapse_http_connection_tcp_initialize_v6_from_url(synapse_http_connection_addr_url pUrl)
{
	synapse_http_connection_handle ptr_handle
		= { .opaque = __synapse_http_connection_tcp_initialize_v6_from_url(pUrl) };

	return ptr_handle;
}

void
synapse_http_conneciton_tcp_cleanup(synapse_http_connection_handle pHandle)
{
	__synapse_http_connection_tcp_cleanup(pHandle.opaque);
}