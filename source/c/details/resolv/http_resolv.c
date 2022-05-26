#include <http/resolv/details/http_resolv.h>

__synapse_http_resolv_result* __synapse_http_resolv_query_v4(synapse_http_resolv_url pUrl)
{
	__synapse_http_resolv_result* ret_result = malloc(sizeof(__synapse_http_resolv_result));
	DNS_STATUS					  ret_status 
		=  DnsQuery(pUrl.url_name, DNS_TYPE_A, DNS_QUERY_BYPASS_CACHE, NULL, &ret_result->entry, NULL);

	return ret_result;
}

__synapse_http_resolv_result* __synapse_http_resolv_query_v6(synapse_http_resolv_url pUrl)
{
	__synapse_http_resolv_result* ret_result = malloc(sizeof(__synapse_http_resolv_result));
	DNS_STATUS					  ret_status 
		= DnsQuery(pUrl.url_name, DNS_TYPE_AAAA, DNS_QUERY_BYPASS_CACHE, NULL, &ret_result->entry, NULL);

	return ret_result;
}

void __synapse_http_resolv_query_cleanup(__synapse_http_resolv_result* pRes)
{
	DnsRecordListFree(pRes->entry, DnsFreeRecordList);
	free			 (pRes);
}

