/*!
 * Design and implementation of the basic RV32I instruction.
 */

#ifndef YTRV_RV32I_H
#define YTRV_RV32I_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include "ytrv/vm.h"

/*!
 * Operation codes of RV32I instruction set.
 */
enum YTRV_RV32I_OPCODES
{
	YTRV_OPCODE_LUI = 0b0110111,
	YTRV_OPCODE_AUIPC = 0b0010111,
	YTRV_OPCODE_JAL = 0b1101111,
	YTRV_OPCODE_JALR = 0b1100111,
	YTRV_OPCODE_BRANCH = 0b1100011,
	YTRV_OPCODE_LOAD = 0b0000011,
	YTRV_OPCODE_STORE = 0b0100011,
	/// Integer Register-Immediate Instructions
	YTRV_OPCODE_OP_IMM = 0b0010011,
	/// Integer Register-Register Instructions
	YTRV_OPCODE_OP = 0b0110011,
	/// Memory Ordering Instructions
	YTRV_OPCODE_MISC_MEM = 0b0001111,
	/// Environment Call and Breakpoints
	YTRV_OPCODE_SYSTEM = 0b1110011,
};

/*!
 *FUNCT3 value for instructions whose OPCODE is YTRV_OPCODE_OP_IMM.
 */
enum YTRV_RV32I_OPCODE_OP_IMM_FUNCT3
{
	YTRV_OPCODE_OP_IMM_FUNCT3_ADDI = 0b000,
	YTRV_OPCODE_OP_IMM_FUNCT3_SLTI = 0b010,
	YTRV_OPCODE_OP_IMM_FUNCT3_SLTIU = 0b011,
	YTRV_OPCODE_OP_IMM_FUNCT3_ANDI = 0b111,
	YTRV_OPCODE_OP_IMM_FUNCT3_ORI = 0b110,
	YTRV_OPCODE_OP_IMM_FUNCT3_XORI = 0b100,
	YTRV_OPCODE_OP_IMM_FUNCT3_SLLI = 0b001,
	YTRV_OPCODE_OP_IMM_FUNCT3_SRLI_SRAI = 0b101,
};

/*!
 *FUNCT3 value for instructions whose OPCODE is YTRV_OPCODE_OP.
 */
enum YTRV_RV32I_OPCODE_OP_FUNCT3
{
	YTRV_OPCODE_OP_FUNCT3_ADD_SUB = 0b000,
	YTRV_OPCODE_OP_FUNCT3_SLT = 0b010,
	YTRV_OPCODE_OP_FUNCT3_SLTU = 0b011,
	YTRV_OPCODE_OP_FUNCT3_AND = 0b111,
	YTRV_OPCODE_OP_FUNCT3_OR = 0b110,
	YTRV_OPCODE_OP_FUNCT3_XOR = 0b100,
	YTRV_OPCODE_OP_FUNCT3_SLL = 0b001,
	YTRV_OPCODE_OP_FUNCT3_SRL_SRA = 0b101,
};

enum YTRV_RV32I_OPCODE_LOAD_FUNCT3
{
	YTRV_OPCODE_LOAD_FUNCT3_LB = 0b000,
	YTRV_OPCODE_LOAD_FUNCT3_LH = 0b001,
	YTRV_OPCODE_LOAD_FUNCT3_LW = 0b010,
	YTRV_OPCODE_LOAD_FUNCT3_LBU = 0b100,
	YTRV_OPCODE_LOAD_FUNCT3_LHU = 0b101,
};

/*!
 * XLEN for RV32I.
 */
static const int YTRV_RV32I_XLEN = 32;

static const int YTRV_RV32I_WORD = 32;

static const int YTRV_RV32I_HALFWORD = 16;

static const int YTRV_RV32I_BYTE = 8;

void ytrv_op_addi(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_slti(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_sltiu(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_andi(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_ori(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_xori(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);
void ytrv_op_slli(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t shamt);
void ytrv_op_srli(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t shamt);
void ytrv_op_srai(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t shamt);

void ytrv_op_add(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_slt(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_sltu(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_and(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_or(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_xor(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_sll(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_srl(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_sub(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_sra(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rsrc2, uint32_t rd);
void ytrv_op_nop(ytrv_vm_t *vm);

void ytrv_op_jal(ytrv_vm_t *vm, uint32_t rd, uint32_t imm);
void ytrv_op_jalr(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd, uint32_t imm);

void ytrv_op_lw(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd);
void ytrv_op_lh(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd);
void ytrv_op_lb(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd);
void ytrv_op_lhu(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd);
void ytrv_op_lbu(ytrv_vm_t *vm, uint32_t rsrc1, uint32_t rd);

/*!
 * LUI (load upper immediate) is used to build 32-bit constants and uses the U-type format. LUI
 * places the U-immediate value in the top 20 bits of the destination register rd, filling in the lowest
 * 12 bits with zeros.
 * @param vm
 * @param rd
 * @param imm
 */
void ytrv_op_lui(ytrv_vm_t *vm, uint32_t rd, uint32_t imm);
/*!
 * AUIPC (add upper immediate to pc) is used to build pc-relative addresses and uses the U-type
 * format. AUIPC forms a 32-bit offset from the 20-bit U-immediate, filling in the lowest 12 bits with
 * zeros, adds this offset to the address of the AUIPC instruction, then places the result in register
 * rd.
 * @param vm
 * @param rd
 * @param imm
 */
void ytrv_op_auipc(ytrv_vm_t *vm, uint32_t rd, uint32_t imm);

/*!
 * The HINT, which is currently implemented as NOP.
 * @param vm
 */
void ytrv_op_hint(ytrv_vm_t *vm);

#ifdef __cplusplus
}
#endif
#endif //YTRV_RV32I_H
