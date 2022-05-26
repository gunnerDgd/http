#include <http/resolv/details/http_resolv_iterate.h>

__synapse_http_resolv_result_iterator*
__synapse_http_resolv_query_iterator_initialize(__synapse_http_resolv_result* pRes)
{
	__synapse_http_resolv_result_iterator* ret_iterator				= malloc(sizeof(__synapse_http_resolv_result_iterator));
										   ret_iterator->ptr_record = pRes->entry;

	return ret_iterator;
}

void
__synapse_http_resolv_query_iterator_cleanup(__synapse_http_resolv_result* pRes)
{
	free(pRes);
}

int
__synapse_http_resolv_query_iterator_next(__synapse_http_resolv_result_iterator* pIterator)
{
	if (pIterator->ptr_record) {
		pIterator->ptr_record = pIterator->ptr_record->pNext;
		return 1;
	}
	else
		return 0;
}

synapse_http_resolv_v4
__synapse_http_resolv_query_iterator_retrieve_v4(__synapse_http_resolv_result_iterator* pIterator)
{
	synapse_http_resolv_v4 ret_v4
		= { .integer = (pIterator->ptr_record->wType == DNS_TYPE_A) ? pIterator->ptr_record->Data.A.IpAddress : 0 };

	return ret_v4;
}

synapse_http_resolv_v6
__synapse_http_resolv_query_iterator_retrieve_v6(__synapse_http_resolv_result_iterator* pIterator)
{
	synapse_http_resolv_v6 ret_v6;
						   ret_v6.integer[0] = (pIterator->ptr_record->wType == DNS_TYPE_AAAA) ? pIterator->ptr_record->Data.AAAA.Ip6Address.IP6Qword[0] : 0;
						   ret_v6.integer[1] = (pIterator->ptr_record->wType == DNS_TYPE_AAAA) ? pIterator->ptr_record->Data.AAAA.Ip6Address.IP6Qword[1] : 0;

	return ret_v6;
}

synapse_http_resolv_url
__synapse_http_resolv_query_iterator_retrieve_cname(__synapse_http_resolv_result_iterator* pIterator)
{
	synapse_http_resolv_url ret_url
		= { .url_name = (pIterator->ptr_record->wType == DNS_TYPE_CNAME) ? pIterator->ptr_record->Data.CNAME.pNameHost : NULL };

	return ret_url;
}