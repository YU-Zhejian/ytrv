//
// Created by yuzj on 23-6-30.
//

#ifndef YUZJ_TINY_RISCV_DEVICE_BUS_H
#define YUZJ_TINY_RISCV_DEVICE_BUS_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "ytrv/dev/dram.h"

typedef struct {
	ytrv_dev_dram_t* dram;
}ytrv_dev_bus_t;

ytrv_dev_bus_t* ytrv_dev_bus_init(uint64_t dram_length);
void ytrv_dev_bus_destroy(ytrv_dev_bus_t* ytrv_dev_bus);

#ifdef __cplusplus
}
#endif

#endif //YUZJ_TINY_RISCV_DEVICE_BUS_H
