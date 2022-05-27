#pragma once
#include <stdint.h>
#include <http/mman/interface/mman.h>

typedef struct __synapse_http_mman_buffering_default_entity_node
{
	void* ptr_buffer;
	size_t current_pointer;

	struct __synapse_http_mman_buffering_default_entity_node*
		next;
} __synapse_http_mman_buffering_default_entity_node;

typedef struct __synapse_http_mman_buffering_default_entity
{
	size_t block_size	 ,
		   entire_count  ,
		   remaining_size;

	__synapse_http_mman_buffering_default_entity_node*
		entry;
	synapse_http_mman_interface
		mman_interface;
} __synapse_http_mman_buffering_default_entity;

__synapse_http_mman_buffering_default_entity*
__synapse_http_mman_buffering_default_initialize(size_t, synapse_http_mman_interface);

void
__synapse_http_mman_buffering_default_cleanup   (__synapse_http_mman_buffering_default_entity*);

__synapse_http_mman_buffering_default_entity_node*
__synapse_http_mman_buffering_default_push_back(size_t);

__synapse_http_mman_buffering_default_entity_node*
__synapse_http_mman_buffering_default_pop_back (size_t);

size_t
__synapse_http_mman_buffering_default_copy_from(__synapse_http_mman_buffering_default_entity*, void*, size_t);

size_t
__synapse_http_mman_buffering_default_copy_to  (__synapse_http_mman_buffering_default_entity*, void*, size_t);