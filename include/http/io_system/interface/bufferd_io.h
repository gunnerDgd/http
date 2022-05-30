#pragma once
#include <http/io_system/interface/io_system.h>

typedef struct synapse_http_io_system_buffered_io
{
	synapse_http_io_system io_system;
	void*				   io_buffer_entity;

	size_t (*read_from)(synapse_http_io_system*, void*, size_t);
	size_t (*write_to) (synapse_http_io_system*, void*, size_t);
	synapse_http_mman_interface
		   (*retrieve_io_buffer)(void*);
	
} synapse_http_io_system_buffered_io;

#define synapse_http_io_system_buffered_io_read_from(pEntity, pReadSize)\
	pEntity.read_from(&pEntity.io_system, pEntity.io_buffer_entity, pReadSize)

#define synapse_http_io_system_buffered_io_write_to(pEntity, pWriteSize)\
	pEntity.write_to (&pEntity.io_system, pEntity.io_buffer_entity, pWriteSize)

#define synapse_http_io_system_buffered_io_retrive_io_buffer(pEntity)\
	pEntity.retrieve_io_buffer(pEntity.io_buffer_entity)