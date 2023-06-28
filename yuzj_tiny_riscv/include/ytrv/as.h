#ifndef YUZJ_TINY_RISCV_AS_H
#define YUZJ_TINY_RISCV_AS_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "ytrv/arith.h"
#include "ytrv/op.h"
#include "ytrv/base.h"


typedef uint32_t ytrv_inst_bin_t;

typedef struct
{
	ytrv_rv32i_operation_t op;
	int n_params;
	uint32_t *params;
} ytrv_inst_opp_t;

ytrv_inst_bin_t ytrv_as_opp_to_bin(ytrv_inst_opp_t opp);

ytrv_inst_opp_t ytrv_as_bin_to_opp(uint32_t ytrv_inst_bin_t);

#ifdef __cplusplus
}
#endif

#endif //YUZJ_TINY_RISCV_AS_H
