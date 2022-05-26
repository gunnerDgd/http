#pragma once
#include <stdint.h>

typedef struct __synapse_transaction_context
{
	void*  req_header     ;
	size_t req_header_size;
	
	void*  req_data       ;
	size_t req_data_size  ;
} __synapse_transaction_context;