#pragma once
#include <stdint.h>

void* __synapse_mman_heap_based_allocate  (void*, void*, size_t);
void  __synapse_mman_heap_based_deallocate(void*, void*, size_t);
void* __synapse_mman_heap_based_resize    (void*, void*, size_t);