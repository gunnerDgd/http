#pragma once
#include <stdint.h>
#include <http/resolv/resolv_types.h>

#include <WinSock2.h>
#include <WS2tcpip.h>

typedef struct synapse_http_connection_handle { void* opaque; } synapse_http_connection_handle  ;

typedef		   synapse_http_resolv_v4							synapse_http_connection_addr_v4 ;
typedef		   synapse_http_resolv_v6							synapse_http_connection_addr_v6 ;
typedef		   synapse_http_resolv_url							synapse_http_connection_addr_url;