#include <http/resolv/resolv_iterate.h>

#include <http/resolv/details/http_resolv.h>
#include <http/resolv/details/http_resolv_iterate.h>

synapse_http_resolv_result_iterator
synapse_http_resolv_query_iterator_initialize(synapse_http_resolv_result pRes)
{
	synapse_http_resolv_result_iterator ret_iterator
		= { .opaque = __synapse_http_resolv_query_iterator_initialize(pRes.opaque) };

	return ret_iterator;
}

void
synapse_http_resolv_query_iterator_cleanup(synapse_http_resolv_result_iterator pIterator)
{
	__synapse_http_resolv_query_iterator_cleanup(pIterator.opaque);
}

int
synapse_http_resolv_query_iterator_next(synapse_http_resolv_result_iterator pIterator)
{
	return __synapse_http_resolv_query_iterator_next(pIterator.opaque);
}

synapse_http_resolv_v4
synapse_http_resolv_query_iterator_retrieve_v4(synapse_http_resolv_result_iterator pIterator)
{
	return __synapse_http_resolv_query_iterator_retrieve_v4(pIterator.opaque);
}

synapse_http_resolv_v6
synapse_http_resolv_query_iterator_retrieve_v6(synapse_http_resolv_result_iterator pIterator)
{
	return __synapse_http_resolv_query_iterator_retrieve_v6(pIterator.opaque);
}

synapse_http_resolv_url
synapse_http_resolv_query_iterator_retrieve_cname(synapse_http_resolv_result_iterator pIterator)
{
	return __synapse_http_resolv_query_iterator_retrieve_cname(pIterator.opaque);
}