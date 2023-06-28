#ifdef __cplusplus
extern "C"
{
#endif
#include "ytrv/arith.h"
#include "ytrv/op.h"


void ytrv_op_addi(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = vm->x[rsrc1] + imm;
}

void ytrv_op_slti(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = ((int32_t)vm->x[rsrc1] < (int32_t)imm);
}

void ytrv_op_sltiu(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] < imm);
}

void ytrv_op_andi(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] & imm);
}

void ytrv_op_ori(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] | imm);
}

void ytrv_op_xori(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] ^ imm);
}

#ifdef __cplusplus
}
#endif