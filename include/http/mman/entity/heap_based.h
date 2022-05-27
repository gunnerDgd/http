#pragma once
#include <http/mman/interface/mman.h>

synapse_http_mman_interface
synapse_http_mman_heap_based_initialize();

void
synapse_http_mman_heap_based_cleanup   (synapse_http_mman_interface);