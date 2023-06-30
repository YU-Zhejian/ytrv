#ifdef __cplusplus
extern "C"
{
#endif
#include <ceu_check/ceu_c_utils.h>

#include "ytrv/dev/bus.h"


ytrv_dev_bus_t* ytrv_dev_bus_init(uint64_t dram_length){
	ytrv_dev_bus_t* ytrv_dev_bus = (ytrv_dev_bus_t*)	ceu_smalloc(sizeof(ytrv_dev_bus_t));
	ytrv_dev_bus->dram = ytrv_dev_dram_init(dram_length);
	return ytrv_dev_bus;
}
void ytrv_dev_bus_destroy(ytrv_dev_bus_t* ytrv_dev_bus){
	if (ytrv_dev_bus == NULL){
		return;
	}
	ytrv_dev_dram_destroy(ytrv_dev_bus->dram);
	ceu_free_non_null(ytrv_dev_bus);
}


#ifdef __cplusplus
}
#endif