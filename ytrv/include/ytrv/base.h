/**
 * YTRV base specifications.
 */

#ifndef YUZJ_TINY_RISCV_BASE_H
#define YUZJ_TINY_RISCV_BASE_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

static inline void ytrv_compiler_check(void)
{
	volatile uint32_t a = 4294967295;
	volatile int32_t b = -1;
	volatile uint32_t c = 1;
	volatile int32_t d = 1;
	volatile uint32_t e = -1;
	assert(a == (uint32_t)b);
	assert(a == e);
	assert(c == d);
	assert((uint32_t)true == 1);
	assert((uint32_t)false == 0);
}

enum YTRV_RV32I_OPCODES
{
	YTRV_OPCODE_LUI = 0b0110111,
	YTRV_OPCODE_AUIPC = 0b0010111,
	YTRV_OPCODE_JAL = 0b1101111,
	YTRV_OPCODE_JALR = 0b1100111,
	YTRV_OPCODE_BRANCH = 0b1100011,
	YTRV_OPCODE_LOAD = 0b0000011,
	YTRV_OPCODE_STORE = 0b0100011,
	YTRV_OPCODE_OP_IMM = 0b0010011,
	YTRV_OPCODE_OP = 0b0110011,
	YTRV_OPCODE_MISC_MEM = 0b0001111,
	YTRV_OPCODE_SYSTEM = 0b1110011,
};

enum YTRV_OPCODE_OP_IMM_FUNCT3
{
	YTRV_OPCODE_OP_IMM_FUNCT3_ADDI = 0b000,
	YTRV_OPCODE_OP_IMM_FUNCT3_SLTI = 0b010,
	YTRV_OPCODE_OP_IMM_FUNCT3_SLTIU = 0b011,
	YTRV_OPCODE_OP_IMM_FUNCT3_ANDI = 0b0111,
	YTRV_OPCODE_OP_IMM_FUNCT3_ORI = 0b110,
	YTRV_OPCODE_OP_IMM_FUNCT3_XORI = 0b100,
	YTRV_OPCODE_OP_IMM_FUNCT3_SLLI = 0b001,
	YTRV_OPCODE_OP_IMM_FUNCT3_SRLI_SRAI = 0b101,

	// case (): // SLTIU (): //  (): // (): //
};

typedef enum
{
	YTRV_OP_ADDI,

} ytrv_rv32i_operation_t;

static const int YTRV_RV32I_XLEN = 32;

static const char YRTV_VERSION[] = "0.0.1";

#endif // YUZJ_TINY_RISCV_BASE_H
