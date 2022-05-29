#pragma once
#include <http/connection/details/http_connection.h>
#include <http/connection/details/http_connection_type.h>

size_t
__synapse_http_connection_tcp_receive_from(__synapse_http_connection_handle_tcp*, uint8_t*, size_t);

size_t
__synapse_http_connection_tcp_send_to	  (__synapse_http_connection_handle_tcp*, uint8_t*, size_t);

size_t
__synapse_http_connection_udp_receive_from(__synapse_http_connection_handle_udp*, uint8_t*, size_t);

size_t
__synapse_http_connection_udp_send_to(__synapse_http_connection_handle_udp*, uint8_t*, size_t);