#ifdef __cplusplus
extern "C"
{
#endif
#include <stdlib.h>
#include <ceu_check/ceu_c_utils.h>

#include "ytrv/dev/bus.h"


ytrv_dev_bus_t *ytrv_dev_bus_init(uint64_t dram_length)
{
	ytrv_dev_bus_t *ytrv_dev_bus = (ytrv_dev_bus_t *)ceu_smalloc(sizeof(ytrv_dev_bus_t));
	ytrv_dev_bus->dram = ytrv_dev_dram_init(dram_length);
	return ytrv_dev_bus;
}
void ytrv_dev_bus_destroy(ytrv_dev_bus_t *ytrv_dev_bus)
{
	if (ytrv_dev_bus == NULL) {
		return;
	}
	ytrv_dev_dram_destroy(ytrv_dev_bus->dram);
	ceu_free_non_null(ytrv_dev_bus);
}

uint64_t ytrv_dev_bus_load(ytrv_dev_bus_t *bus, uint64_t address, int length)
{
	if ((YTRV_DEV_DRAM_BASE <= address) & (address < bus->dram->end)) {
		return ytrv_dev_dram_load(bus->dram, address, length);
	}
	abort(); // TODO: Except
}

uint8_t ytrv_dev_bus_load_uint8(ytrv_dev_bus_t *bus, uint64_t address)
{
	return (uint8_t)ytrv_dev_bus_load(bus, address, 8);
}
uint16_t ytrv_dev_bus_load_uint16(ytrv_dev_bus_t *bus, uint64_t address)
{
	return (uint16_t)ytrv_dev_bus_load(bus, address, 16);
}
uint32_t ytrv_dev_bus_load_uint32(ytrv_dev_bus_t *bus, uint64_t address)
{
	return (uint32_t)ytrv_dev_bus_load(bus, address, 32);
}
uint64_t ytrv_dev_bus_load_uint64(ytrv_dev_bus_t *bus, uint64_t address)
{
	return ytrv_dev_bus_load(bus, address, 64);
}

void ytrv_dev_bus_save(ytrv_dev_bus_t *bus, uint64_t address, uint64_t value, int length)
{
	if ((YTRV_DEV_DRAM_BASE <= address) & (address < bus->dram->end)) {
		ytrv_dev_dram_save(bus->dram, address, value, length);
	}
	else {
		ceu_die_with_retv("Bus address violation", 1);
	}
}

void ytrv_dev_bus_save_uint8(ytrv_dev_bus_t *bus, uint64_t address, uint8_t value)
{
	ytrv_dev_bus_save(bus, address, value, 8);
}
void ytrv_dev_bus_save_uint16(ytrv_dev_bus_t *bus, uint64_t address, uint16_t value)
{
	ytrv_dev_bus_save(bus, address, value, 16);
}
void ytrv_dev_bus_save_uint32(ytrv_dev_bus_t *bus, uint64_t address, uint32_t value)
{
	ytrv_dev_bus_save(bus, address, value, 32);
}
void ytrv_dev_bus_save_uint64(ytrv_dev_bus_t *bus, uint64_t address, uint64_t value)
{
	ytrv_dev_bus_save(bus, address, value, 64);
}


#ifdef __cplusplus
}
#endif