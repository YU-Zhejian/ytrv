#ifndef YUZJ_TINY_RISCV_VM_H
#define YUZJ_TINY_RISCV_VM_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct ytrv_vm
{
	void *memory;
	uint32_t *x; // General-purposed registers
	uint32_t pc; // Program Counter register
} ytrv_vm_t;

ytrv_vm_t *ytrv_vm_init(bool init_mem);

void ytrv_vm_destroy(ytrv_vm_t *vm);

void ytrv_vm_exec_single(ytrv_vm_t *vm, uint32_t instruction);

#ifdef __cplusplus
}
#endif

#endif //YUZJ_TINY_RISCV_VM_H
