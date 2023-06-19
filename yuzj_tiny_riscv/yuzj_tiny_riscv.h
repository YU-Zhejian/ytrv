#include <stdint.h>
#include <math.h>
#include <ceu_check/ceu_c_utils.h>


const enum YTRV_RV32I_OPCODES {
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

const int YTRV_RV32I_XLEN = 32;

typedef struct ytrv_vm {
	void* memory;
	uint32_t* x; // General-purposed registers
	uint32_t pc; // Program Counter register
} ytrv_vm_t;

inline static ytrv_vm_t* ytrv_vm_init() {
	ytrv_vm_t* vm = (ytrv_vm_t*)ceu_smalloc(sizeof(ytrv_vm_t));
	vm->memory = ceu_smalloc((size_t)pow(2, YTRV_RV32I_XLEN));
	vm->x = (uint32_t*) ceu_scalloc(32, sizeof(uint32_t));
	vm->x[0] = 0; // Set register 0 to 0.
	vm->pc = 0;
	return vm;
}

inline static void ytrv_vm_destroy(ytrv_vm_t* vm) {
	ceu_free_non_null(vm->memory);
	ceu_free_non_null(vm->x);
	ceu_free_non_null(vm);
}


inline static uint32_t ytrv_uint32_sub(uint32_t src_int, int from_pos, int to_pos) {
	return (src_int >> from_pos);
}

inline static void ytrv_vm_exec_single(ytrv_vm_t* vm, uint32_t instruction) {
	int opcode = instruction % 128;
	printf("EXEC_TRACE INSTRUCT OPCODE 0x%x\n", opcode);
	switch (opcode)
	{
	case OPCODE_OP_IMM: // Integer Register-Immediate Instructions
		// TODO
		uint8_t rs1 = instruction ; // Source register
		uint8_t rd = ; // Destination register

		break;
	default:
		// TODO: Except
		break;
	}
}


inline static void ytrv_vm_exec(ytrv_vm_t* vm, uint32_t* instructions) {
	
}
