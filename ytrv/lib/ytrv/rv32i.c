#ifdef __cplusplus
extern "C"
{
#endif
#include "ytrv/arith.h"
#include "ytrv/rv32i.h"


void ytrv_op_addi(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = vm->x[rsrc1] + imm;
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_slti(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = ((int32_t)vm->x[rsrc1] < (int32_t)imm);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_sltiu(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] < imm);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_andi(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] & imm);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_ori(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] | imm);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_xori(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] ^ imm);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_slli(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t shamt)
{
	vm->x[rd] = (vm->x[rsrc1] << shamt);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_srli(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t shamt)
{
	vm->x[rd] = (vm->x[rsrc1] >> shamt);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_srai(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t shamt)
{
	vm->x[rd] = ytrv_sign_extend(
		(vm->x[rsrc1] >> shamt),
		32 - shamt
	);
	ytrv_vm_advance_pc(vm);
}

void ytrv_op_add(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = vm->x[rsrc1] + vm->x[rsrc2];
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_slt(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = ((int32_t)vm->x[rsrc1] < (int32_t)vm->x[rsrc2]);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_sltu(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = (vm->x[rsrc1] < vm->x[rsrc2]);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_and(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = (vm->x[rsrc1] & vm->x[rsrc2]);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_or(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = (vm->x[rsrc1] | vm->x[rsrc2]);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_xor(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = (vm->x[rsrc1] ^ vm->x[rsrc2]);
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_sll(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = (vm->x[rsrc1] << (vm->x[rsrc2] & 0b11111));
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_srl(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = (vm->x[rsrc1] <<  (vm->x[rsrc2] & 0b11111));
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_sub(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = vm->x[rsrc1] - vm->x[rsrc2];
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_sra(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd)
{
	vm->x[rd] = ytrv_sign_extend(
		(vm->x[rsrc1] >> (vm->x[rsrc2] & 0b11111)),
		32 - (vm->x[rsrc2] & 0b11111)
	);
	ytrv_vm_advance_pc(vm);
}

void ytrv_op_nop(ytrv_vm_t *vm)
{
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_hint(ytrv_vm_t *vm)
{
	ytrv_vm_advance_pc(vm);
}

void ytrv_op_jal(ytrv_vm_t *vm, uint32_t rd, uint32_t imm){
	// FIXME: Not finished
	if (rd != YTRV_VM_REGISTER_ZERO)
	{ // J opcode, which is jump without setting register
		vm->x[rd] = vm->pc;
	}
	vm->pc = vm->pc + imm;
}

void ytrv_op_jalr(ytrv_vm_t *vm,uint32_t rsrc1, uint32_t rd, uint32_t imm){
	// FIXME: Not finished
}

void ytrv_op_lui(ytrv_vm_t *vm, uint32_t rd, uint32_t imm){
	vm->x[rd] = imm << 12;
	ytrv_vm_advance_pc(vm);
}
void ytrv_op_auipc(ytrv_vm_t *vm, uint32_t rd, uint32_t imm){
	vm->x[rd] = (imm << 12) + vm->pc;
	ytrv_vm_advance_pc(vm);
}

#ifdef __cplusplus
}
#endif