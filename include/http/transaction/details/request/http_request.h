#pragma once
#include <http/connection/connection_tcp.h>
#include <http/connection/connection_type.h>

#include <http/transaction/details/http_transaction_type.h>
#include <http/mman/buffering/mman_buffering_entity.h>

__synapse_transaction_context
__synapse_transaction_receive_from(synapse_http_connection_handle, synapse_http_mman_buffering_entity);

size_t
__synapse_transaction_send_to     (synapse_http_connection_handle, __synapse_transaction_context);