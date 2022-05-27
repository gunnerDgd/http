#pragma once
#include <http/mman/interface/mman.h>
#include <http/mman/interface/mman_buffering.h>

synapse_http_mman_buffering_entity
synapse_http_mman_buffering_default_initialize(size_t, synapse_http_mman_interface);

void
synapse_http_mman_buffering_default_cleanup   (synapse_http_mman_buffering_entity);