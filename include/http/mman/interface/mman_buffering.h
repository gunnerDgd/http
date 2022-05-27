#pragma once
#include <stdint.h>

typedef struct synapse_http_mman_buffering_entity
{
	size_t (*copy_from)		 (void*, void*, size_t);
	size_t (*copy_to)	     (void*, void*, size_t);

	size_t (*entire_size)    (void*);
	size_t (*remaining_size) (void*);

	void*    entity;
} synapse_http_mman_buffering_entity;