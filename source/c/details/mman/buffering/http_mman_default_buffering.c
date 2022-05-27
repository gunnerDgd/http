#pragma once
#include <http/mman/details/buffering/http_mman_default_buffering.h>
#include <string.h>

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
		   ptr_buffer->backmost = ptr_buffer->entry;
	return ptr_buffer;
}

void
__synapse_http_mman_buffering_default_cleanup(__synapse_http_mman_buffering_default_entity* pBuffer)
{

}

__synapse_http_mman_buffering_default_entity_node*
__synapse_http_mman_buffering_default_push_back(__synapse_http_mman_buffering_default_entity* pEntity, size_t pCount)
{
	__synapse_http_mman_buffering_default_entity_node* ptr_pback_node
		= pEntity->backmost;
	for (size_t it_cnt = 0		; 
				it_cnt < pCount ; 
				it_cnt++, ptr_pback_node = ptr_pback_node->next)
		ptr_pback_node->next =
			pEntity->mman_interface.allocate(pEntity->mman_interface.entity, 
											 ptr_pback_node				   , 
											 sizeof(__synapse_http_mman_buffering_default_entity_node));
	pEntity->entire_count   +=  pCount;
	pEntity->remaining_size += (pCount * pEntity->block_size);
	
		   ptr_pback_node->next = NULL;
	return ptr_pback_node;
}

__synapse_http_mman_buffering_default_entity_node*
__synapse_http_mman_buffering_default_pop_back(__synapse_http_mman_buffering_default_entity* pEntity, size_t pCount)
{
	__synapse_http_mman_buffering_default_entity_node* ptr_pback_node
		= pEntity->entry;

	for ( ; ptr_pback_node->current_pointer 
		  ; ptr_pback_node = ptr_pback_node->next);

	while (pCount && ptr_pback_node)
	{
		__synapse_http_mman_buffering_default_entity_node* ptr_erase
			= ptr_pback_node;

		ptr_pback_node = ptr_pback_node->next;
		pEntity->mman_interface.deallocate(pEntity->mman_interface.entity, ptr_erase, sizeof(__synapse_http_mman_buffering_default_entity_node));
		
	}
}

size_t
__synapse_http_mman_buffering_default_copy_from(__synapse_http_mman_buffering_default_entity* pBuffer, uint8_t* pSource, size_t pSize)
{
	__synapse_http_mman_buffering_default_entity_node*
		ptr_node_seek = pBuffer->backmost;

	if(pBuffer->remaining_size < pSize)
		__synapse_http_mman_buffering_default_push_back(pBuffer,
														__synapse_http_mman_buffering_default_round_size(pBuffer->block_size, pSize));

	size_t		sz_copy_to = 0;
	for (size_t sz_copied = 0	  ; 
				sz_copied < pSize ; 
				sz_copied += sz_copy_to, ptr_node_seek = ptr_node_seek->next)
	{
		sz_copy_to = ((pBuffer->block_size - ptr_node_seek->current_pointer) > pSize)
				   ?  (pBuffer->block_size - ptr_node_seek->current_pointer)
				   :   pSize;

		memcpy(ptr_node_seek->ptr_buffer + ptr_node_seek->current_pointer,
			   pSource + sz_copied,
			   sz_copy_to);
	}
	
	return pSize;
}

size_t
__synapse_http_mman_buffering_default_copy_to(__synapse_http_mman_buffering_default_entity* pBuffer, uint8_t* pDest, size_t pSize)
{
	__synapse_http_mman_buffering_default_entity_node*
		ptr_node_seek = pBuffer->backmost;
	size_t
		sz_copy_to    = ((pBuffer->entire_count * pBuffer->block_size - pBuffer->remaining_size) < pSize)
					  ?  (pBuffer->entire_count * pBuffer->block_size - pBuffer->remaining_size)
					  :   pSize,
		sz_copy_to_round = 0;

	for (size_t sz_copied = 0		   ; 
				sz_copied < sz_copy_to ;
				ptr_node_seek = ptr_node_seek->next,
				sz_copied += sz_copy_to_round)
	{
		sz_copy_to_round = ((sz_copy_to - sz_copied) > ptr_node_seek->current_pointer) 
						 ? ptr_node_seek->current_pointer 
						 :  (sz_copy_to - sz_copied);

		memcpy(pDest + sz_copied		, 
			   ptr_node_seek->ptr_buffer,
			   sz_copy_to_round);
	}

	return sz_copy_to;
}

size_t
__synapse_http_mman_buffering_default_entire_size(__synapse_http_mman_buffering_default_entity* pEntity)
{
	return pEntity->entire_count * pEntity->block_size;
}

size_t
__synapse_http_mman_buffering_default_remaining_size(__synapse_http_mman_buffering_default_entity* pEntity)
{
	return pEntity->remaining_size;
}