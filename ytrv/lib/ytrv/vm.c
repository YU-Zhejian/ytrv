#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <log.h>
#include <ceu_check/ceu_c_utils.h>

#include "ytrv/base.h"
#include "ytrv/arith.h"
#include "ytrv/vm.h"
#include "ytrv/op.h"


ytrv_vm_t *ytrv_vm_init(size_t initial_memory_size)
{
	ytrv_vm_t *vm = (ytrv_vm_t *)ceu_smalloc(sizeof(ytrv_vm_t));
	if (initial_memory_size != 0) {
		vm->memory = (uint32_t*) ceu_smalloc(initial_memory_size);
	}
	else {
		vm->memory = NULL;
	}
	vm->x = (uint32_t *)ceu_scalloc(32, sizeof(uint32_t));
	vm->x[YTRV_VM_REGISTER_ZERO] = 0;
	vm->x[YTRV_VM_REGISTER_SP] = initial_memory_size-1;
	vm->pc = 0;
	return vm;
}

void ytrv_vm_destroy(ytrv_vm_t *vm)
{
	ceu_free_non_null(vm->memory);
	ceu_free_non_null(vm->x);
	ceu_free_non_null(vm);
}

uint32_t ytrv_vm_fetch(ytrv_vm_t *vm){
	uint32_t idx = vm->pc;
	return vm->memory[idx];
}

void ytrv_vm_op_imm(ytrv_vm_t *vm, uint32_t instruction){
	// Define all possible names
	uint32_t rd; // Destination register
	uint32_t funct3;// Operation
	uint32_t rsrc1;  // Source register
	uint32_t imm; // Sign-Extended Immediate number
	uint32_t shamt; // Shift amount
	rd = ytrv_uint32_sub(instruction, 7, 12);
	funct3 = ytrv_uint32_sub(instruction, 12, 15);
	rsrc1 = ytrv_uint32_sub(instruction, 15, 20);
	switch (funct3) {
		case (YTRV_OPCODE_OP_IMM_FUNCT3_ADDI):
			;
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			);
			log_debug("EXEC_INST ADDI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
			ytrv_op_addi(vm, rsrc1, rd, imm);
			break;
		case (YTRV_OPCODE_OP_IMM_FUNCT3_SLTI):
			;
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			); // Immediate number
			log_debug("EXEC_INST SLTI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
			ytrv_op_slti(vm, rsrc1, rd, imm);
			break;
		case (YTRV_OPCODE_OP_IMM_FUNCT3_SLTIU):
			;
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			); // Immediate number
			log_debug("EXEC_INST SLTIU(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
			ytrv_op_sltiu(vm, rsrc1, rd, imm);
			break;
		case (YTRV_OPCODE_OP_IMM_FUNCT3_ANDI):
			;
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			); // Immediate number
			if ((imm == 0) & (rsrc1 == 0) & (rd == 0)) { // NOP
				break;
			}
			log_debug("EXEC_INST ANDI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
			ytrv_op_andi(vm, rsrc1, rd, imm);
			break;
		case (YTRV_OPCODE_OP_IMM_FUNCT3_ORI):
			;
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			); // Immediate number
			log_debug("EXEC_INST ORI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
			ytrv_op_ori(vm, rsrc1, rd, imm);
			break;
		case (YTRV_OPCODE_OP_IMM_FUNCT3_XORI):
			;
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			); // Immediate number
			log_debug("EXEC_INST XORI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
			ytrv_op_xori(vm, rsrc1, rd, imm);
			break;
		case (YTRV_OPCODE_OP_IMM_FUNCT3_SLLI):
			;
			shamt = ytrv_uint32_sub(instruction, 20, 25);
			log_debug("EXEC_INST SLLI(SRC=%d, DEST=%d, SHAMT=%d) \n", rsrc1, rd, shamt);
			ytrv_op_slli(vm, rsrc1, rd, shamt);
			break;
		case (YTRV_OPCODE_OP_IMM_FUNCT3_SRLI_SRAI):
			shamt = ytrv_uint32_sub(instruction, 20, 25);
			switch (ytrv_uint32_sub(instruction, 25, 32)) {
				case (0): // SRLI
					;
					log_debug("EXEC_INST SRLI(SRC=%d, DEST=%d, SHAMT=%d) \n", rsrc1, rd, shamt);
					ytrv_op_srli(vm, rsrc1, rd, shamt);
					break;
				case(0b0100000): // SRAI
					;
					log_debug("EXEC_INST SRAI(SRC=%d, DEST=%d, SHAMT=%d) \n", rsrc1, rd, shamt);
					ytrv_op_srai(vm, rsrc1, rd, shamt);
					break;
				default:
					; // TODO: Except
					break;
			}
			;
			break;
		default:
			// TODO: Except
			break;
	}
}

void ytrv_vm_exec_single(ytrv_vm_t *vm, uint32_t instruction)
{
	uint32_t opcode = ytrv_uint32_sub(instruction, 0, 7);
	printf("EXEC_TRACE INSTRUCT OPCODE 0x%x\n", opcode);
	switch (opcode) {
		case YTRV_OPCODE_OP_IMM: // Integer Register-Immediate Instructions
			;
			ytrv_vm_op_imm(vm, instruction);
			break;
		default:
			// TODO: Except
			break;
	}
}

#ifdef __cplusplus
}
#endif