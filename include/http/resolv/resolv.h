#pragma once
#include <stdint.h>
#include <http/resolv/resolv_types.h>

synapse_http_resolv_result 
synapse_http_resolv_query_v4(synapse_http_resolv_url);

synapse_http_resolv_result
synapse_http_resolv_query_v6(synapse_http_resolv_url);

void
synapse_http_resolv_query_cleanup(synapse_http_resolv_result);