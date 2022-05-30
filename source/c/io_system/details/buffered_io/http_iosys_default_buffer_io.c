#include <http/io_system/details/buffered_io/http_iosys_default_buffer_io.h>
#include <http/mman/entity/heap_based.h>

#include <stdlib.h>
#include <string.h>

synapse_http_io_system_buffered_io
__synapse_http_io_system_buffered_io_default_initialize(synapse_http_io_system* pIoSys)
{
	synapse_http_io_system_buffered_io ptr_bufio =
	{
		.io_buffer_entity = __synapse_http_mman_buffering_default_initialize(1024 * 4,
							  synapse_http_mman_heap_based_initialize()),
		.io_system		  = pIoSys,
		.read_from		  = &__synapse_http_io_system_buffered_io_default_read_from,
		.write_to		  = &__synapse_http_io_system_buffered_io_default_write_to
	};

	return ptr_bufio;
}

void
__synapse_http_io_system_buffered_io_default_cleanup(synapse_http_io_system_buffered_io pBufferedIo) {}

size_t
__synapse_http_io_system_buffered_io_default_read_from(synapse_http_io_system* pIoSys, void* pReadBuffer, size_t pReadSize)
{
	__synapse_http_mman_buffering_default_entity* 
		ptr_buffer = pReadBuffer;
	__synapse_http_mman_buffering_default_entity_node* 
		ptr_rdptr  = ptr_buffer->current;
	
	if(ptr_buffer->remaining_size < pReadSize)
		__synapse_http_mman_buffering_default_push_back (ptr_buffer, 
		__synapse_http_mman_buffering_default_round_size(ptr_buffer->block_size, pReadSize));

		size_t sz_read_round = 0;
	for(size_t sz_read = 0					   ;
			   sz_read < pReadSize && ptr_rdptr;
			   ptr_rdptr = ptr_rdptr->next,
			   sz_read += sz_read_round)
	{
		sz_read_round = ((ptr_buffer->block_size - ptr_rdptr->current_pointer) > (pReadSize - sz_read))
					  ? (pReadSize - sz_read)
					  : (ptr_buffer->block_size - ptr_rdptr->current_pointer);

		synapse_http_io_system_read_from((*pIoSys), 
										 ptr_rdptr->ptr_buffer + ptr_rdptr->current_pointer, 
										 sz_read_round);
	}

	return pReadSize;
}

size_t
__synapse_http_io_system_buffered_io_default_write_to(synapse_http_io_system* pIoSys, void* pWriteBuffer, size_t pWriteSize)
{
	__synapse_http_mman_buffering_default_entity* 
		ptr_buffer = pWriteBuffer;
	__synapse_http_mman_buffering_default_entity_node* 
		ptr_wrptr  = ptr_buffer->current;

	size_t sz_write_size = (pWriteSize > (ptr_buffer->entire_count * ptr_buffer->block_size))
						 ?				 (ptr_buffer->entire_count * ptr_buffer->block_size)
						 :				  pWriteSize;
		
	for(size_t sz_write = 0					      ;
			   sz_write < sz_write_size&& ptr_wrptr;
			   ptr_wrptr = ptr_wrptr->next,
			   sz_write += ptr_wrptr->current_pointer)
	{
		
		synapse_http_io_system_write_to((*pIoSys)			   ,
										  ptr_wrptr->ptr_buffer,
										  ptr_wrptr->current_pointer);
	}

	return sz_write_size;
}