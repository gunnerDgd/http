#include <http/connection/details/io_base/http_connection_io_base.h>

size_t
__synapse_http_connection_tcp_receive_from(__synapse_http_connection_handle_tcp* pTcp, uint8_t* pBuffer, size_t pSize)
{
	return recv(pTcp->conn_handle, pBuffer, pSize, 0);
}

size_t
__synapse_http_connection_tcp_send_to(__synapse_http_connection_handle_tcp* pTcp, uint8_t* pBuffer, size_t pSize)
{
	return send(pTcp->conn_handle, pBuffer, pSize, 0);
}