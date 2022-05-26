#pragma once
#include <stdint.h>

typedef struct synapse_http_resolv_url
{
	wchar_t* url_name  ;
	uint16_t url_length;
} synapse_http_resolv_url;

typedef struct synapse_http_resolv_v4
{
	union
	{
		uint8_t  byte[4];
		uint32_t integer;
	};

	uint16_t port;
} synapse_http_resolv_v4;

typedef struct synapse_http_resolv_v6
{
	union
	{
		uint8_t  byte   [16];
		uint64_t integer[2] ;
	};

	uint16_t port;
} synapse_http_resolv_v6;

typedef struct synapse_http_resolv_result		   { void* opaque; } synapse_http_resolv_result			;
typedef struct synapse_http_resolv_result_iterator { void* opaque; } synapse_http_resolv_result_iterator;