#ifndef YUZJ_TINY_RISCV_OP_H
#define YUZJ_TINY_RISCV_OP_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include "ytrv/vm.h"

void ytrv_op_addi(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_slti(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_sltiu(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_andi(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_ori(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_xori(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);

#ifdef __cplusplus
}
#endif
#endif //YUZJ_TINY_RISCV_OP_H
