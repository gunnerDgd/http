#include <http/mman/details/entity/http_mman_heap_based.h>
#include <http/mman/entity/heap_based.h>

synapse_http_mman_interface
synapse_http_mman_heap_based_initialize()
{
	synapse_http_mman_interface ptr_interface =
	{
		.allocate   = &__synapse_mman_heap_based_allocate  ,
		.deallocate = &__synapse_mman_heap_based_deallocate,
		.resize     = &__synapse_mman_heap_based_resize
	};

	return ptr_interface;
}

void
synapse_http_mman_heap_based_cleanup(synapse_http_mman_interface pInterface) { /* Do Nothing */ }