#include <http/connection/details/http_connection.h>

#include <http/resolv/resolv.h>
#include <http/resolv/resolv_iterate.h>

__synapse_http_connection_handle_tcp*
__synapse_http_connection_tcp_initialize_from_v4(synapse_http_connection_addr_v4 pV4)
{
	SOCKADDR_IN							  addr_handle;
	__synapse_http_connection_handle_tcp* ptr_handle
		= malloc(sizeof(__synapse_http_connection_handle_tcp));

	addr_handle.sin_addr.S_un.S_addr = pV4.integer;
	addr_handle.sin_port			 = pV4.port   ;
	addr_handle.sin_family			 = AF_INET    ;

	ptr_handle->conn_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	connect  (ptr_handle->conn_handle, &addr_handle, sizeof(SOCKADDR_IN));
	return    ptr_handle;
}

__synapse_http_connection_handle_tcp*
__synapse_http_connection_tcp_initialize_from_v6(synapse_http_connection_addr_v6 pV6)
{
	// Under Construction.
	return NULL;
}

__synapse_http_connection_handle_tcp*
__synapse_http_connection_tcp_initialize_v4_from_url(synapse_http_connection_addr_url pUrl)
{
	synapse_http_resolv_result			res_resolv			= synapse_http_resolv_query_v4				   (pUrl)	   ;
	synapse_http_resolv_result_iterator res_resolv_iterator = synapse_http_resolv_query_iterator_initialize(res_resolv);
	synapse_http_connection_addr_v4		res_v4;

	while (TRUE)
	{
		res_v4 = synapse_http_resolv_query_iterator_retrieve_v4(res_resolv_iterator);
		if (!res_v4.integer) {
			pUrl	   = synapse_http_resolv_query_iterator_retrieve_cname(res_resolv_iterator);
			res_resolv = synapse_http_resolv_query_v4					  (pUrl);
						 synapse_http_resolv_query_iterator_cleanup		  (res_resolv_iterator);

			if(!pUrl.url_name) return NULL;
			
			res_resolv_iterator
				= synapse_http_resolv_query_iterator_initialize(res_resolv);
		}
		else
			break;
	}

	return __synapse_http_connection_tcp_initialize_from_v4(res_v4);
}

__synapse_http_connection_handle_tcp*
__synapse_http_connection_tcp_initialize_v6_from_url(synapse_http_connection_addr_url pUrl)
{
	synapse_http_resolv_result			res_resolv			= synapse_http_resolv_query_v6				   (pUrl)	   ;
	synapse_http_resolv_result_iterator res_resolv_iterator = synapse_http_resolv_query_iterator_initialize(res_resolv);
	synapse_http_connection_addr_v6		res_v6;

	while (TRUE)
	{
		res_v6 = synapse_http_resolv_query_iterator_retrieve_v6(res_resolv_iterator);
		if (!res_v6.integer[0] && !res_v6.integer[1]) {
			pUrl	   = synapse_http_resolv_query_iterator_retrieve_cname(res_resolv_iterator);
			res_resolv = synapse_http_resolv_query_v6					  (pUrl);
						 synapse_http_resolv_query_iterator_cleanup		  (res_resolv_iterator);

			if(!pUrl.url_name) return NULL;
			
			res_resolv_iterator
				= synapse_http_resolv_query_iterator_initialize(res_resolv);
		}
		else
			break;
	}

	return __synapse_http_connection_tcp_initialize_from_v6(res_v6);
}

void __synapse_http_connection_tcp_cleanup(__synapse_http_connection_handle_tcp* pTcpConn)
{
	closesocket(pTcpConn->conn_handle);
	free	   (pTcpConn);
}