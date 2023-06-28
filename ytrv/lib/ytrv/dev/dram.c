/*!
 * Header for a basic DRAM.
 */
#ifdef __cplusplus
extern "C"
{
#endif
#include <ceu_check/ceu_c_utils.h>

#include "ytrv/dev/dram.h"
#include "ytrv/base.h"

uint8_t ytrv_dev_dram_load_uint8(ytrv_dev_dram_t *dram, uint64_t address){
	CEU_ENSURE_NOT_NONE(dram);
	return dram->mem[address];
}
uint16_t ytrv_dev_dram_load_uint16(ytrv_dev_dram_t *dram, uint64_t address);
uint32_t ytrv_dev_dram_load_uint32(ytrv_dev_dram_t *dram, uint64_t address);
uint64_t ytrv_dev_dram_load_uint64(ytrv_dev_dram_t *dram, uint64_t address);

void ytrv_dev_dram_save_uint8(ytrv_dev_dram_t *dram, uint64_t address, uint8_t value);
void ytrv_dev_dram_save_uint16(ytrv_dev_dram_t *dram, uint64_t address, uint16_t value);
void ytrv_dev_dram_save_uint32(ytrv_dev_dram_t *dram, uint64_t address, uint32_t value);
void ytrv_dev_dram_save_uint64(ytrv_dev_dram_t *dram, uint64_t address, uint64_t value);

ytrv_dev_dram_t* ytrv_dev_dram_init(uint64_t length){
	ytrv_dev_dram_t* ytrv_dev_dram = (ytrv_dev_dram_t*)ceu_smalloc(sizeof(ytrv_dev_dram_t));
	ytrv_dev_dram->length=length;
	ytrv_dev_dram->mem  = (uint8_t*)ceu_scalloc(length, sizeof(uint8_t));
	return ytrv_dev_dram;
}
void ytrv_dev_dram_destroy(ytrv_dev_dram_t* ytrv_dev_dram){
	if (ytrv_dev_dram == NULL){
		return;
	}
	ceu_free_non_null(ytrv_dev_dram->mem);
	ceu_free_non_null(ytrv_dev_dram);
}

#ifdef __cplusplus
}
#endif

