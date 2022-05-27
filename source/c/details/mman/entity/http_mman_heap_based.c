#include <http/mman/details/entity/http_mman_heap_based.h>
#include <stdlib.h>

void* __synapse_mman_heap_based_allocate  (void* pHandle, void* pHint   , size_t pSize) { return malloc (pSize)		  ; }
void  __synapse_mman_heap_based_deallocate(void* pHandle, void* pDealloc, size_t pSize) {		 free   (pDealloc)	  ; }
void* __synapse_mman_heap_based_resize	  (void* pHandle, void* pHint   , size_t pSize) { return realloc(pHint, pSize); }