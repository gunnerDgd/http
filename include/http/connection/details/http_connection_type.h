#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <http/connection/connection_type.h>

typedef struct __synapse_http_connection_handle_tcp
{
	SOCKET conn_handle		  ;
	int    conn_address_family;
	union
	{
		SOCKADDR_IN  conn_address   ;
		SOCKADDR_IN6 conn_address_v6;
	};
} __synapse_http_connection_handle_tcp;

typedef struct __synapse_http_connection_handle_udp
{
	SOCKET conn_handle		  ;
	int    conn_address_family;
	union
	{
		SOCKADDR_IN  conn_address	;
		SOCKADDR_IN6 conn_address_v6;
	};
} __synapse_http_connection_handle_udp;