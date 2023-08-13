/*!
 * Header for a basic little-endian DRAM.
 */
#ifdef __cplusplus
extern "C"
{
#endif
#include <ceu_c_utils.h>

#include "ytrv/dev/dram.h"

uint64_t ytrv_dev_dram_load(ytrv_dev_dram_t *dram, uint64_t address, int length)
{
	CEU_ENSURE_NOT_NONE(dram);
	uint64_t reti = 0;
	uint64_t index = address - YTRV_DEV_DRAM_BASE;
	uint64_t immi;
	for (int i = 0; i < length / YTRV_DEV_DRAM_BYTE_LENGTH; i++) {
		immi = (uint64_t) dram->mem[index + i];
		reti |= (immi << (YTRV_DEV_DRAM_BYTE_LENGTH * i));
	}
	return reti;
}

uint8_t ytrv_dev_dram_load_uint8(ytrv_dev_dram_t *dram, uint64_t address)
{
	return (uint8_t)ytrv_dev_dram_load(dram, address, 8);
}
uint16_t ytrv_dev_dram_load_uint16(ytrv_dev_dram_t *dram, uint64_t address)
{
	return (uint16_t)ytrv_dev_dram_load(dram, address, 16);
}
uint32_t ytrv_dev_dram_load_uint32(ytrv_dev_dram_t *dram, uint64_t address)
{
	return (uint32_t)ytrv_dev_dram_load(dram, address, 32);
}
uint64_t ytrv_dev_dram_load_uint64(ytrv_dev_dram_t *dram, uint64_t address)
{
	return (uint64_t)ytrv_dev_dram_load(dram, address, 64);
}

void ytrv_dev_dram_save(ytrv_dev_dram_t *dram, uint64_t address, uint64_t value, int length)
{
	CEU_ENSURE_NOT_NONE(dram);
	uint8_t seti;
	uint64_t index = address - YTRV_DEV_DRAM_BASE;
	for (int i = 0; i < length / YTRV_DEV_DRAM_BYTE_LENGTH; i++) {
		seti = (value >> (YTRV_DEV_DRAM_BYTE_LENGTH * i)) & 0xff; //0b11111111
		dram->mem[index + i] = seti;
	}
}

void ytrv_dev_dram_save_uint8(ytrv_dev_dram_t *dram, uint64_t address, uint8_t value)
{
	ytrv_dev_dram_save(dram, address, value, 8);
}
void ytrv_dev_dram_save_uint16(ytrv_dev_dram_t *dram, uint64_t address, uint16_t value)
{
	ytrv_dev_dram_save(dram, address, value, 16);
}
void ytrv_dev_dram_save_uint32(ytrv_dev_dram_t *dram, uint64_t address, uint32_t value)
{
	ytrv_dev_dram_save(dram, address, value, 32);
}
void ytrv_dev_dram_save_uint64(ytrv_dev_dram_t *dram, uint64_t address, uint64_t value)
{
	ytrv_dev_dram_save(dram, address, value, 64);
}

ytrv_dev_dram_t *ytrv_dev_dram_init(uint64_t length)
{
	ytrv_dev_dram_t *ytrv_dev_dram = (ytrv_dev_dram_t *)ceu_smalloc(sizeof(ytrv_dev_dram_t));
	ytrv_dev_dram->length = length;
	ytrv_dev_dram->mem = (uint8_t *)ceu_scalloc(length, sizeof(uint8_t));
	ytrv_dev_dram->end = ytrv_dev_dram->length + YTRV_DEV_DRAM_BASE - 1;
	return ytrv_dev_dram;
}
void ytrv_dev_dram_destroy(ytrv_dev_dram_t *ytrv_dev_dram)
{
	if (ytrv_dev_dram == NULL) {
		return;
	}
	ceu_free_non_null(ytrv_dev_dram->mem);
	ceu_free_non_null(ytrv_dev_dram);
}

#ifdef __cplusplus
}
#endif

