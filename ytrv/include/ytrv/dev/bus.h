#ifndef YUZJ_TINY_RISCV_DEVICE_BUS_H
#define YUZJ_TINY_RISCV_DEVICE_BUS_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "ytrv/dev/dram.h"

typedef struct
{
	ytrv_dev_dram_t *dram;
} ytrv_dev_bus_t;

ytrv_dev_bus_t *ytrv_dev_bus_init(uint64_t dram_length);
void ytrv_dev_bus_destroy(ytrv_dev_bus_t *ytrv_dev_bus);

/**
 * Real bus load implementation.
 *
 * @param bus
 * @param address
 * @param length
 * @return
 */
uint64_t ytrv_dev_bus_load(ytrv_dev_bus_t *bus, uint64_t address, int length);
uint8_t ytrv_dev_bus_load_uint8(ytrv_dev_bus_t *bus, uint64_t address);
uint16_t ytrv_dev_bus_load_uint16(ytrv_dev_bus_t *bus, uint64_t address);
uint32_t ytrv_dev_bus_load_uint32(ytrv_dev_bus_t *bus, uint64_t address);
uint64_t ytrv_dev_bus_load_uint64(ytrv_dev_bus_t *bus, uint64_t address);

void ytrv_dev_bus_save(ytrv_dev_bus_t *bus, uint64_t address, uint64_t value, int length);
void ytrv_dev_bus_save_uint8(ytrv_dev_bus_t *bus, uint64_t address, uint8_t value);
void ytrv_dev_bus_save_uint16(ytrv_dev_bus_t *bus, uint64_t address, uint16_t value);
void ytrv_dev_bus_save_uint32(ytrv_dev_bus_t *bus, uint64_t address, uint32_t value);
void ytrv_dev_bus_save_uint64(ytrv_dev_bus_t *bus, uint64_t address, uint64_t value);

#ifdef __cplusplus
}
#endif

#endif //YUZJ_TINY_RISCV_DEVICE_BUS_H
