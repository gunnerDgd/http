#pragma once
#include <stdio.h>
#include <stdint.h>

#define synapse_http_debug_message(module_name, msg)\
	printf("[SYNAPSE-HTTP][DEBUG][%s] :: %s\n", module_name, msg)

#define synapse_http_debug_memory_message(module_name, val_name, memory)\
	printf("[SYNAPSE-HTTP][MEMORY_DEBUG][%s] :: Variable [%s] = %08x\n", module_name, val_name, memory)

#define synapse_http_debug_memory_hexview(module_name, memory_area, size)\
	for(size_t it_hex = 0 ; it_hex < size ; it_hex++){\
		if(it_hex % 16  == 0) printf("\n");\
		printf("%02x ", memory_area[it_hex]);\
	}