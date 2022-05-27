#include <http/mman/buffering/default_buffering.h>
#include <http/mman/details/buffering/http_mman_default_buffering.h>

synapse_http_mman_buffering_entity
synapse_http_mman_buffering_default_initialize(size_t pBlockSize, synapse_http_mman_interface pMman)
{
	synapse_http_mman_buffering_entity ptr_entity = 
	{
		.copy_from		= &__synapse_http_mman_buffering_default_copy_from	   ,
		.copy_to        = &__synapse_http_mman_buffering_default_copy_to       ,
		.entire_size    = &__synapse_http_mman_buffering_default_entire_size   ,
		.remaining_size = &__synapse_http_mman_buffering_default_remaining_size,
		.entity			=  __synapse_http_mman_buffering_default_initialize(pBlockSize, pMman)
	};

	return ptr_entity;
}

void
synapse_http_mman_buffering_default_cleanup(synapse_http_mman_buffering_entity pEntity)
{
	__synapse_http_mman_buffering_default_cleanup(pEntity.entity);
}