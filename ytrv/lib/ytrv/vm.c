#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <log.h>
#include <ceu_check/ceu_c_utils.h>
#include <stdlib.h>

#include "ytrv/base.h"
#include "ytrv/arith.h"
#include "ytrv/vm.h"
#include "ytrv/rv32i.h"


ytrv_vm_t *ytrv_vm_init(uint32_t initial_memory_size)
{
	ytrv_compiler_check();
	ytrv_vm_t *vm = (ytrv_vm_t *)ceu_smalloc(sizeof(ytrv_vm_t));
	if (initial_memory_size == 0) {
		initial_memory_size = 16 * 1024 * 1024;
	}
	vm->bus = ytrv_dev_bus_init(initial_memory_size);
	vm->x = (uint32_t *)ceu_scalloc(32, sizeof(uint32_t));
	vm->x[YTRV_VM_REGISTER_ZERO] = 0;
	vm->x[YTRV_VM_REGISTER_SP] = initial_memory_size - 1;
	vm->pc = 0;
	return vm;
}

void ytrv_vm_destroy(ytrv_vm_t *vm)
{
	ytrv_dev_bus_destroy(vm->bus);
	ceu_free_non_null(vm->x);
	ceu_free_non_null(vm);
}

/*!
 * Fetch another instruction from PC.
 *
 * @param vm
 * @return The fetched instruction in uint32_t.
 */
uint32_t ytrv_vm_fetch_instruction(ytrv_vm_t *vm)
{
	return ytrv_dev_bus_load_uint32(vm->bus, vm->pc);
}

/*!
 * Integer Register-Immediate Instructions, including ADDI, SLTI, SLTIU, ANDI, ORI, XORI, SLLI, SRLI, SRAI.
 *
 * @param vm
 * @param instruction
 */
void ytrv_vm_op_imm(ytrv_vm_t *vm, uint32_t instruction)
{
	// Define all possible names
	uint32_t rd; // Destination register
	uint32_t funct3;// Operation
	uint32_t funct7;// Operation
	uint32_t rsrc1;  // Source register
	uint32_t imm; // Sign-Extended Immediate number
	uint32_t shamt; // Shift amount
	rd = ytrv_uint32_sub(instruction, 7, 12);
	funct3 = ytrv_uint32_sub(instruction, 12, 15);
	rsrc1 = ytrv_uint32_sub(instruction, 15, 20);
	funct7 = ytrv_uint32_sub(instruction, 25, 32);
	switch (funct3) {
		case (YTRV_OPCODE_OP_IMM_FUNCT3_ADDI):

			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			);
			if ((imm == 0) & (rd == YTRV_VM_REGISTER_ZERO) & (rsrc1 == YTRV_VM_REGISTER_ZERO)) { // NOP
				log_debug("EXEC_INST NOP() \n");
				ytrv_op_nop(vm);
				break;
			}
			else if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST ADDI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
				ytrv_op_addi(vm, rsrc1, rd, imm);
				break;
			}
		case (YTRV_OPCODE_OP_IMM_FUNCT3_SLTI):
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			);
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST SLTI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
				ytrv_op_slti(vm, rsrc1, rd, imm);
				break;
			}
		case (YTRV_OPCODE_OP_IMM_FUNCT3_SLTIU):
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			); // Immediate number
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST SLTIU(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
				ytrv_op_sltiu(vm, rsrc1, rd, imm);
				break;
			}
		case (YTRV_OPCODE_OP_IMM_FUNCT3_ANDI):
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			);
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST ANDI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
				ytrv_op_andi(vm, rsrc1, rd, imm);
				break;
			}
		case (YTRV_OPCODE_OP_IMM_FUNCT3_ORI):
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			);
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST ORI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
				ytrv_op_ori(vm, rsrc1, rd, imm);
				break;
			}
		case (YTRV_OPCODE_OP_IMM_FUNCT3_XORI):
			imm = ytrv_sign_extend(
				ytrv_uint32_sub(instruction, 20, 32),
				12
			);
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST XORI(SRC=%d, DEST=%d, IMMNUM=%d) \n", rsrc1, rd, imm);
				ytrv_op_xori(vm, rsrc1, rd, imm);
				break;
			}
		case (YTRV_OPCODE_OP_IMM_FUNCT3_SLLI): shamt = ytrv_uint32_sub(instruction, 20, 25);
			log_debug("EXEC_INST SLLI(SRC=%d, DEST=%d, SHAMT=%d) \n", rsrc1, rd, shamt);
			ytrv_op_slli(vm, rsrc1, rd, shamt);
			break;
		case (YTRV_OPCODE_OP_IMM_FUNCT3_SRLI_SRAI): shamt = ytrv_uint32_sub(instruction, 20, 25);
			switch (funct7) {
				case (0):
					if (rd == YTRV_VM_REGISTER_ZERO) {
						log_debug("EXEC_INST HINT() \n");
						ytrv_op_hint(vm);
						break;
					}
					else {
						log_debug("EXEC_INST SRLI(SRC=%d, DEST=%d, SHAMT=%d) \n", rsrc1, rd, shamt);
						ytrv_op_srli(vm, rsrc1, rd, shamt);
						break;
					}
				case (0b0100000):
					if (rd == YTRV_VM_REGISTER_ZERO) {
						log_debug("EXEC_INST HINT() \n");
						ytrv_op_hint(vm);
						break;
					}
					else {
						log_debug("EXEC_INST SRAI(SRC=%d, DEST=%d, SHAMT=%d) \n", rsrc1, rd, shamt);
						ytrv_op_srai(vm, rsrc1, rd, shamt);
						break;
					}
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

/*!
 * Integer Register-Register Instructions, including ADD, SUB, SLT, SLTU, AND, OR, XOR, SLL, SRL, SRA
 *
 * @param vm
 * @param instruction
 */
void ytrv_vm_op(ytrv_vm_t *vm, uint32_t instruction)
{
	// Define all possible names
	uint32_t rd; // Destination register
	uint32_t funct3;// Operation
	uint32_t funct7;// Operation
	uint32_t rsrc1;  // Source register 1
	uint32_t rsrc2; // Source register 2
	rd = ytrv_uint32_sub(instruction, 7, 12);
	funct3 = ytrv_uint32_sub(instruction, 12, 15);
	rsrc1 = ytrv_uint32_sub(instruction, 15, 20);
	rsrc2 = ytrv_uint32_sub(instruction, 20, 25);
	funct7 = ytrv_uint32_sub(instruction, 25, 32);

	switch (funct3) {
		case (YTRV_OPCODE_OP_FUNCT3_ADD_SUB):
			switch (funct7) {
				case 0:
					if (rd == YTRV_VM_REGISTER_ZERO) {
						log_debug("EXEC_INST HINT() \n");
						ytrv_op_hint(vm);
						break;
					}
					else {
						log_debug("EXEC_INST ADD(SRC1=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
						ytrv_op_add(vm, rsrc1, rsrc2, rd);
						break;
					}
				case 0b0100000:
					if (rd == YTRV_VM_REGISTER_ZERO) {
						log_debug("EXEC_INST HINT() \n");
						ytrv_op_hint(vm);
						break;
					}
					else {
						log_debug("EXEC_INST SUB(SRC1=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
						ytrv_op_sub(vm, rsrc1, rsrc2, rd);
						break;
					}
				default:
					// TODO: Except
					break;
			}
			break;
		case (YTRV_OPCODE_OP_FUNCT3_SLT):
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST SLT(SRC=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
				ytrv_op_slt(vm, rsrc1, rsrc2, rd);
				break;
			}
		case (YTRV_OPCODE_OP_FUNCT3_SLTU):
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST SLTU(SRC=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
				ytrv_op_sltu(vm, rsrc1, rsrc2, rd);
				break;
			}
		case (YTRV_OPCODE_OP_FUNCT3_AND):
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST AND(SRC=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
				ytrv_op_and(vm, rsrc1, rsrc2, rd);
				break;
			}
		case (YTRV_OPCODE_OP_FUNCT3_XOR):
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST XOR(SRC=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
				ytrv_op_xor(vm, rsrc1, rsrc2, rd);
				break;
			}
		case (YTRV_OPCODE_OP_FUNCT3_OR):
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST OR(SRC=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
				ytrv_op_or(vm, rsrc1, rsrc2, rd);
				break;
			}
		case (YTRV_OPCODE_OP_FUNCT3_SLL):
			if (rd == YTRV_VM_REGISTER_ZERO) {
				log_debug("EXEC_INST HINT() \n");
				ytrv_op_hint(vm);
				break;
			}
			else {
				log_debug("EXEC_INST SLL(SRC=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);

				ytrv_op_sll(vm, rsrc1, rsrc2, rd);
				break;
			}
		case (YTRV_OPCODE_OP_FUNCT3_SRL_SRA):
			switch (funct7) {
				case (0): // SRL
					if (rd == YTRV_VM_REGISTER_ZERO) {
						log_debug("EXEC_INST HINT() \n");
						ytrv_op_hint(vm);
						break;
					}
					else {
						log_debug("EXEC_INST SRL(SRC=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
						ytrv_op_srl(vm, rsrc1, rsrc2, rd);
						break;
					}
				case (0b0100000): // SRA
					if (rd == YTRV_VM_REGISTER_ZERO) {
						log_debug("EXEC_INST HINT() \n");
						ytrv_op_hint(vm);
						break;
					}
					else {
						log_debug("EXEC_INST SRA(SRC=%d, SRC2=%d, DEST=%d) \n", rsrc1, rsrc2, rd);
						ytrv_op_sra(vm, rsrc1, rsrc2, rd);
						break;
					}
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

void ytrv_vm_lui(ytrv_vm_t *vm, uint32_t instruction)
{
	// Define all possible names
	uint32_t rd; // Destination register
	uint32_t imm; // Immediate number
	rd = ytrv_uint32_sub(instruction, 7, 12);
	imm = ytrv_uint32_sub(instruction, 12, 32);
	if (rd == YTRV_VM_REGISTER_ZERO) {
		log_debug("EXEC_INST HINT() \n");
		ytrv_op_hint(vm);
	}
	else {
		log_debug("EXEC_INST LUI(DEST=%d, IMMNUM=%d) \n", rd, imm);
		ytrv_op_lui(vm, rd, imm);
	}
}

void ytrv_vm_aupic(ytrv_vm_t *vm, uint32_t instruction)
{
	// Define all possible names
	uint32_t rd; // Destination register
	uint32_t imm; // Immediate number
	rd = ytrv_uint32_sub(instruction, 7, 12);
	imm = ytrv_uint32_sub(instruction, 12, 32);
	if (rd == YTRV_VM_REGISTER_ZERO) {
		log_debug("EXEC_INST HINT() \n");
		ytrv_op_hint(vm);
	}
	else {
		log_debug("EXEC_INST AUIPC(DEST=%d, IMMNUM=%d) \n", rd, imm);
		ytrv_op_auipc(vm, rd, imm);
	}
}

void ytrv_vm_fence(ytrv_vm_t *vm, uint32_t instruction)
{
	// Define all possible names
	uint32_t rd; // Destination register
	rd = ytrv_uint32_sub(instruction, 7, 12);
	if (rd == YTRV_VM_REGISTER_ZERO) {
		log_debug("EXEC_INST HINT() \n");
		ytrv_op_hint(vm);
	}
	else {
		log_debug("EXEC_INST FENCE() \n");
		ytrv_op_nop(vm); // TODO
	}
}


void ytrv_vm_ecall_ebreak(ytrv_vm_t *vm, uint32_t instruction)
{
	// Define all possible names
	uint32_t funct12;
	funct12 = ytrv_uint32_sub(instruction, 20, 32);
	switch (funct12) {
		case 0: // ECALL
			log_debug("EXEC_INST ECALL() \n");
			ytrv_op_nop(vm); // TODO
			break;
		case 1:// EBREAK
			log_debug("EXEC_INST EBREAK() \n");
			abort(); // TODO
		default:
			// TODO: EXCEPT
			break;
	}

}

void ytrv_vm_exec_single(ytrv_vm_t *vm, uint32_t instruction)
{
	uint32_t opcode = ytrv_uint32_sub(instruction, 0, 7);
	printf("EXEC_TRACE INSTRUCT OPCODE 0x%x\n", opcode);
	switch (opcode) {
		case YTRV_OPCODE_OP_IMM: ytrv_vm_op_imm(vm, instruction);
			break;
		case YTRV_OPCODE_OP: ytrv_vm_op(vm, instruction);
			break;
		case YTRV_OPCODE_JAL: break;// TODO
		case YTRV_OPCODE_JALR: break; // TODO
		case YTRV_OPCODE_LUI: ytrv_vm_lui(vm, instruction);
			break;
		case YTRV_OPCODE_AUIPC: ytrv_vm_aupic(vm, instruction);
			break;
		case YTRV_OPCODE_LOAD: break; // TODO
		case YTRV_OPCODE_STORE: break; // TODO
		case YTRV_OPCODE_BRANCH: break; // TODO
		case YTRV_OPCODE_MISC_MEM: ytrv_vm_fence(vm, instruction);
			break;
		case YTRV_OPCODE_SYSTEM: ytrv_vm_ecall_ebreak(vm, instruction);
			break;
		default:
			// TODO: Except
			break;
	}
}

void ytrv_vm_exec(ytrv_vm_t *vm)
{
	// Set PC to memory start
	vm->pc = YTRV_DEV_DRAM_BASE;
	while (true) {
		ytrv_vm_exec_single(vm, ytrv_vm_fetch_instruction(vm));
	}
}

void ytrv_vm_advance_pc(ytrv_vm_t *vm)
{
	vm->pc += 4;
}

#ifdef __cplusplus
}
#endif