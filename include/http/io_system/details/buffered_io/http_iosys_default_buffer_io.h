#pragma once
#include <http/mman/details/buffering/http_mman_default_buffering.h>
#include <http/io_system/interface/bufferd_io.h>

synapse_http_io_system_buffered_io
__synapse_http_io_system_buffered_io_default_initialize(synapse_http_io_system*);

void
__synapse_http_io_system_buffered_io_default_cleanup   (synapse_http_io_system_buffered_io);

size_t
__synapse_http_io_system_buffered_io_default_read_from(synapse_http_io_system*, void*, size_t);

size_t
__synapse_http_io_system_buffered_io_default_write_to (synapse_http_io_system*, void*, size_t);