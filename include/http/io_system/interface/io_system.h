#pragma once
#include <stdint.h>

typedef struct synapse_http_io_system
{
	size_t(*read_from)(void*, void*, size_t);
	size_t(*write_to) (void*, void*, size_t);

	void*   io_entity;
} synapse_http_io_system;

#define synapse_http_io_system_read_from(pEntity, pReadBuffer, pReadSize)\
	pEntity.read_from(pEntity.io_entity, pReadBuffer, pReadSize)

#define synapse_http_io_system_write_to(pEntity, pWriteBuffer, pWriteSize)\
	pEntity.write_to (pEntity.io_entity, pWriteBuffer, pWriteSize)