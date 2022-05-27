#pragma once
#include <http/mman/details/buffering/http_mman_default_buffering.h>

__synapse_http_mman_buffering_default_entity*
__synapse_http_mman_buffering_default_initialize(size_t pBlockSize, synapse_http_mman_interface pMmanInterface)
{
	__synapse_http_mman_buffering_default_entity* ptr_buffer
		= pMmanInterface.allocate(pMmanInterface.entity, NULL, sizeof(__synapse_http_mman_buffering_default_entity));

	ptr_buffer->block_size     = pBlockSize	   ;
	ptr_buffer->entire_count   = 1			   ;
	ptr_buffer->mman_interface = pMmanInterface;
	ptr_buffer->remaining_size = pBlockSize    ;

	ptr_buffer->entry
		= ptr_buffer->mman_interface.allocate(ptr_buffer->mman_interface.entity,
											  ptr_buffer,
											  sizeof(__synapse_http_mman_buffering_default_entity_node));

	return ptr_buffer;
}

void
__synapse_http_mman_buffering_default_cleanup(__synapse_http_mman_buffering_default_entity* pBuffer)
{

}

size_t
__synapse_http_mman_buffering_default_copy_from(__synapse_http_mman_buffering_default_entity* pBuffer, void* pSource, size_t pSize)
{
	__synapse_http_mman_buffering_default_entity_node*
		ptr_node_seek = pBuffer->entry;

	for (; ptr_node_seek; ptr_node_seek = ptr_node_seek->next)
		if ((ptr_node_seek->current_pointer + pSize) < pBuffer->block_size) 
			break;

	if (!ptr_node_seek) // No Buffer to Copy...
		 ptr_node_seek = __synapse_http_mman_buffering_default_push_back(pBuffer->entire_count * 2);

	
}

size_t
__synapse_http_mman_buffering_default_copy_to(__synapse_http_mman_buffering_default_entity*, void*, size_t);