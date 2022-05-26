#pragma once
#include <Windows.h>
#include <WinDNS.h>

#include <http/resolv/resolv_types.h>

typedef struct __synapse_http_resolv_result
{
	PDNS_RECORD entry;
}__synapse_http_resolv_result;

typedef struct __synapse_http_resolv_result_iterator
{
	PDNS_RECORD ptr_record;
} __synapse_http_resolv_result_iterator;

__synapse_http_resolv_result* __synapse_http_resolv_query_v4	 (synapse_http_resolv_url)	    ;
__synapse_http_resolv_result* __synapse_http_resolv_query_v6	 (synapse_http_resolv_url)	    ;
void						  __synapse_http_resolv_query_cleanup(__synapse_http_resolv_result*);

