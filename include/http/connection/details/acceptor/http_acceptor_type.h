#pragma once
#include <WS2tcpip.h>
#include <WinSock2.h>

typedef struct __synapse_http_connection_acceptor_tcp_handle
{
	SOCKET acpt_conn  ;
	int    acpt_family;

	union
	{
		SOCKADDR_IN  acpt_address	;
		SOCKADDR_IN6 acpt_address_v6;
	};
} __synapse_http_connection_acceptor_tcp_handle;

typedef struct __synapse_http_connection_acceptor_udp_handle
{
	SOCKET acpt_conn;
	int    acpt_family;

	union
	{
		SOCKADDR_IN  acpt_address;
		SOCKADDR_IN6 acpt_address_v6;
	};
} __synapse_http_connection_acceptor_udp_handle;