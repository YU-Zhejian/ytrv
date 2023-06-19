
#include <math.h>
#include <stdio.h>

#include "yuzj_tiny_riscv.h"
#include "ceu_check/ceu_c_utils.h"
#include "ceu_check/ceu_check_all.h"


void print_version_info()
{
	char* cbuff = get_full_info();
	printf("%s\n", cbuff);
	ceu_free_non_null(cbuff);
}


int main() {
	printf("YUZJ TINY RISCV RV32I VM\n");
	printf("Allocating memory...\n");
	ytrv_vm_t* vm = ytrv_vm_init();
	printf("Allocating memory SUCCESS\n");
	ytrv_vm_exec_single(vm, 0b11111111111111111000111110010011);

	printf("Deallocating memory...\n");
	ytrv_vm_destroy(vm);
	printf("Deallocating memory SUCCESS\n");
	puts("Press any key to exit...");
	getchar();
	return 0;
}
