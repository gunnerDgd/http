#pragma once
#include <http/connection/details/http_connection.h>
#include <http/io_system/interface/io_system.h>

synapse_http_io_system
__synapse_http_io_system_tcp_initialize		 (__synapse_http_connection_handle_tcp);

void
__synapse_http_io_system_tcp_cleanup		 (synapse_http_io_system);

size_t __synapse_http_io_system_tcp_read_from(void*, void*, size_t);
size_t __synapse_http_io_system_tcp_write_to (void*, void*, size_t);