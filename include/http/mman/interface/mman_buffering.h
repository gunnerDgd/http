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

#define synapse_http_mman_buffering_copy_from(pEntity, pSource, pSize)\
	pEntity.copy_from(pEntity.entity, pSource, pSize)

#define synapse_http_mman_buffering_copy_to(pEntity, pDestination, pSize)\
	pEntity.copy_to(pEntity.entity, pDestination, pSize)

#define synapse_http_mman_buffering_entire_size(pEntity)\
	pEntity.entire_size(pEntity.entity)

#define synapse_http_mman_buffering_remaining_size(pEntity)\
	pEntity.remaining_size(pEntity.entity)