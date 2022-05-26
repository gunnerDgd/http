#include <http/connection/details/acceptor/http_acceptor_tcp.h>

__synapse_http_connection_acceptor_tcp_handle*
__synapse_http_connection_acceptor_tcp_initialize_from_v4(synapse_http_connection_addr_v4 pConf)
{
	__synapse_http_connection_acceptor_tcp_handle* ptr_handle
		= malloc(sizeof(__synapse_http_connection_acceptor_tcp_handle));

	ptr_handle->acpt_family						  = AF_INET												;
	ptr_handle->acpt_conn						  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ptr_handle->acpt_address.sin_addr.S_un.S_addr =	pConf.integer										;
	ptr_handle->acpt_address.sin_port			  = htons(pConf.port)						    ;
	ptr_handle->acpt_address.sin_family			  = AF_INET												;

	return ptr_handle;
}

__synapse_http_connection_acceptor_tcp_handle*
__synapse_http_connection_acceptor_tcp_initialize_from_v6(synapse_http_connection_addr_v6 pConf)
{
	/*
	* Under Construction.
	*/

	// Do not use this function until construction is completed.
	return NULL;
}

void
__synapse_http_connection_acceptor_tcp_bind_v4(__synapse_http_connection_acceptor_tcp_handle* pHandle)
{
	bind(pHandle->acpt_conn, &pHandle->acpt_address, sizeof(SOCKADDR_IN));
}

void
__synapse_http_connection_acceptor_tcp_listen(__synapse_http_connection_acceptor_tcp_handle* pHandle, int pBacklog)
{
	listen(pHandle->acpt_conn, pBacklog);
}

__synapse_http_connection_handle_tcp*
__synapse_http_connection_acceptor_tcp_accept(__synapse_http_connection_acceptor_tcp_handle* pHandle)
{
	int									  addr_size = (pHandle->acpt_family == AF_INET) ? sizeof(SOCKADDR_IN)
																						: sizeof(SOCKADDR_IN6);
	__synapse_http_connection_handle_tcp* ptr_handle
		= malloc(sizeof(__synapse_http_connection_handle_tcp));

		   ptr_handle->conn_handle = accept(pHandle->acpt_conn, &pHandle->acpt_address, &addr_size);
	return ptr_handle;
}

void
__synapse_http_connection_acceptor_tcp_cleanup(__synapse_http_connection_acceptor_tcp_handle* pHandle)
{
	closesocket(pHandle->acpt_conn);
	free	   (pHandle)		   ;
}