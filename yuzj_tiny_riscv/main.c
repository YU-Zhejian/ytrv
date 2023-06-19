
#include <math.h>

#include "yuzj_tiny_riscv.h"
#include "ceu_check/ceu_c_utils.h"



int main() {
	printf("YUZJ TINY RISCV RV32I VM\n");
	printf("Allocating memory...\n");
	ytrv_vm_t* vm = ytrv_vm_init();
	printf("Allocating memory SUCCESS\n");
	ytrv_vm_exec_single(vm, 0b11111111111111111111111110100011);

	printf("Deallocating memory...\n");
	ytrv_vm_destroy(vm);
	printf("Deallocating memory SUCCESS\n");
	return 0;
}
