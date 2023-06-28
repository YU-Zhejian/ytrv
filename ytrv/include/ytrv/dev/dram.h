/*!
 * Header for a basic DRAM.
 */

#ifndef YUZJ_TINY_RISCV_DEVICE_DRAM_H
#define YUZJ_TINY_RISCV_DEVICE_DRAM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef struct
{
	uint64_t length;
	uint8_t *mem;
} ytrv_dev_dram_t;

uint8_t ytrv_dev_dram_load_uint8(ytrv_dev_dram_t *dram, uint64_t address);
uint16_t ytrv_dev_dram_load_uint16(ytrv_dev_dram_t *dram, uint64_t address);
uint32_t ytrv_dev_dram_load_uint32(ytrv_dev_dram_t *dram, uint64_t address);
uint64_t ytrv_dev_dram_load_uint64(ytrv_dev_dram_t *dram, uint64_t address);

void ytrv_dev_dram_save_uint8(ytrv_dev_dram_t *dram, uint64_t address, uint8_t value);
void ytrv_dev_dram_save_uint16(ytrv_dev_dram_t *dram, uint64_t address, uint16_t value);
void ytrv_dev_dram_save_uint32(ytrv_dev_dram_t *dram, uint64_t address, uint32_t value);
void ytrv_dev_dram_save_uint64(ytrv_dev_dram_t *dram, uint64_t address, uint64_t value);

ytrv_dev_dram_t* ytrv_dev_dram_init(uint64_t length);
void ytrv_dev_dram_destroy(ytrv_dev_dram_t* ytrv_dev_dram);

#ifdef __cplusplus
}
#endif

#endif //YUZJ_TINY_RISCV_DEVICE_DRAM_H
