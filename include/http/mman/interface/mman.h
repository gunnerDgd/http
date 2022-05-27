#pragma once
#include <stdint.h>

typedef struct synapse_http_mman_interface
{
	void*   entity;
	void* (*allocate)  (void*, void*, size_t);
	void  (*deallocate)(void*, void*, size_t);
	void* (*resize)    (void*, void*, size_t);
} synapse_http_mman_interface;

#define synapse_http_mman_inteface_allocate(pInterface, pHint, pSize)\
	pInterface->allocate(pInterface->entity, pHint, pSize)

#define synapse_http_mman_inteface_deallocate(pInterface, pDealloc, pSize)\
	pInterface->allocate(pInterface->entity, pDealloc, pSize)

#define synapse_http_mman_inteface_resize(pInterface, pHint, pSize)\
	pInterface->allocate(pInterface->entity, pHint, pSize)