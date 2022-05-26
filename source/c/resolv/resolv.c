#include <http/resolv/resolv.h>

#include <http/resolv/details/http_resolv.h>
#include <http/resolv/details/http_resolv_iterate.h>

synapse_http_resolv_result synapse_http_resolv_query_v4(synapse_http_resolv_url pUrl)
{
	synapse_http_resolv_result ret_result
		= { .opaque = __synapse_http_resolv_query_v4(pUrl) }; return ret_result;
}

synapse_http_resolv_result
synapse_http_resolv_query_v6(synapse_http_resolv_url pUrl)
{
	synapse_http_resolv_result ret_result
		= { .opaque = __synapse_http_resolv_query_v6(pUrl) }; return ret_result;
}

void
synapse_http_resolv_query_cleanup(synapse_http_resolv_result pRes)
{
	__synapse_http_resolv_query_cleanup(pRes.opaque);
}