#pragma once
#include <stdint.h>

typedef struct synapse_http_mman_buffering_entity
{
	size_t (*copy_from)		 (void*, void*, size_t);
	size_t (*copy_to)	     (void*, void*, size_t);

	size_t (*entire_size)    (void*);
	size_t (*remaining_size) (void*);

	size_t (*current_pointer)(void*);
	size_t (*move_pointer)   (void*, size_t);

	void*    entity			   ;
	void*  (*initialize)()	   ;
	void   (*cleanup)   (void*);
} synapse_http_mman_buffering_entity;

typedef struct synapse_http_mman_buffer { void* opaque; };