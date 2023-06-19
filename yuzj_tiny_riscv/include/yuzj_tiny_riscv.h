#ifndef YUZJ_TINY_RISCV_H
#define YUZJ_TINY_RISCV_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "ceu_check/ceu_c_utils.h"


enum YTRV_RV32I_OPCODES
{
	OPCODE_LUI = 0b0110111,
	OPCODE_AUIPC = 0b0010111,
	OPCODE_JAL = 0b1101111,
	OPCODE_JALR = 0b1100111,
	OPCODE_BRANCH = 0b1100011,
	OPCODE_LOAD = 0b0000011,
	OPCODE_STORE = 0b0100011,
	OPCODE_OP_IMM = 0b0010011,
	OPCODE_OP = 0b0110011,
	OPCODE_MISC_MEM = 0b0001111,
	OPCODE_SYSTEM = 0b1110011,
};

static const int YTRV_RV32I_XLEN = 32;

// Arithmetic functions

uint32_t ytrv_uint32_sub(uint32_t src_int, uint8_t from_pos, uint8_t to_pos);

uint32_t ytrv_sign_extend(uint32_t src_num, uint8_t msb);

/*!
 * Convert unsigned number to signed number.
 *
 * @param src_num The source number. Should be less than 2^31.
 * @param is_positive Whether it is positive.
 * @return Converted number. Would set highest bit to 1 for negative numbers.
 */
uint32_t ytrv_unsigned_to_signed(uint32_t src_num, bool is_positive);

uint32_t ytrv_get_msb(uint32_t src_num);

// VM-related params
typedef struct ytrv_vm
{
	void* memory;
	uint32_t* x; // General-purposed registers
	uint32_t pc; // Program Counter register
} ytrv_vm_t;

ytrv_vm_t* ytrv_vm_init();

void ytrv_vm_destroy(ytrv_vm_t* vm);

void ytrv_vm_exec_single(ytrv_vm_t* vm, uint32_t instruction);

void ytrv_vm_exec(ytrv_vm_t* vm, uint32_t* instructions);

uint32_t ytrv_to_negative(uint32_t src_num);

#ifdef __cplusplus
}
#endif
#endif // YUZJ_TINY_RISCV_H
