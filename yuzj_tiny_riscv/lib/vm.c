#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

#include "yuzj_tiny_riscv.h"

ytrv_vm_t* ytrv_vm_init()
{
	ytrv_vm_t* vm = (ytrv_vm_t*)ceu_smalloc(sizeof(ytrv_vm_t));
	vm->memory = ceu_smalloc((size_t)1 << YTRV_RV32I_XLEN);
	vm->x = (uint32_t*)ceu_scalloc(32, sizeof(uint32_t));
	vm->x[0] = 0; // Set register 0 to 0.
	vm->pc = 0;
	return vm;
}

void ytrv_vm_destroy(ytrv_vm_t* vm)
{
	ceu_free_non_null(vm->memory);
	ceu_free_non_null(vm->x);
	ceu_free_non_null(vm);
}


void ytrv_vm_addi(ytrv_vm_t* vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = vm->x[rsrc1] + imm;
}
void ytrv_vm_slti(ytrv_vm_t* vm, uint32_t rsrc1, uint32_t rd, uint32_t imm)
{
	vm->x[rd] = (vm->x[rsrc1] < imm); // FIXME
}

void ytrv_vm_exec_single(ytrv_vm_t* vm, uint32_t instruction)
{
	uint32_t opcode = ytrv_uint32_sub(instruction, 0, 7);
	printf("EXEC_TRACE INSTRUCT OPCODE 0x%x\n", opcode);
	// Define all possible names
	uint32_t rd ; // Destination register
	uint32_t funct3;// Operation
	uint32_t rsrc1;  // Source register
	uint32_t imm; // Sign-Extended Immediate number
	switch (opcode)
	{
	case OPCODE_OP_IMM: // Integer Register-Immediate Instructions
		;
		rd = ytrv_uint32_sub(instruction, 7, 12);
		funct3 = ytrv_uint32_sub(instruction, 12, 15);
		rsrc1 = ytrv_uint32_sub(instruction, 15, 20);
		switch (funct3)
		{
		case (0b000): // ADDI
			;
			imm = ytrv_sign_extend(
					ytrv_uint32_sub(instruction, 20, 32),
					12
			);
			printf("EXEC_INST ADDI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
			ytrv_vm_addi(vm, rsrc1, rd, imm);
			break;
		case (0b010): // SLTI
			;
			uint32_t imm = ytrv_sign_extend(
					ytrv_uint32_sub(instruction, 20, 32),
					12
			); // Immediate number
			printf("EXEC_INST SLTI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
			ytrv_vm_slti(vm, rsrc1, rd, imm);
			break;
		default:
			// TODO: Except
			break;
		}
		break;
	default:
		// TODO: Except
		break;
	}
}


void ytrv_vm_exec(ytrv_vm_t* vm, uint32_t* instructions)
{

}

#ifdef __cplusplus
}
#endif