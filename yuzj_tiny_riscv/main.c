#include <stdio.h>
#include <ceu_check/ceu_c_utils.h>
#include <ceu_check/ceu_check_all.h>
#include <log.h>

#include "ytrv/vm.h"


void print_version_info()
{
	char *cbuff = get_full_info();
	printf("%s\n", cbuff);
	ceu_free_non_null(cbuff);
}

int main()
{
	log_set_level(LOG_INFO);
	FILE *log_file = fopen("log.log", "a");
	if (log_file == NULL) {
		ceu_die_with_retv("Cannot open log!", 1);
	}
	log_add_fp(log_file, LOG_TRACE);
	log_info("YUZJ TINY RISCV RV32I VM");
	log_info("Version info");
	print_version_info();
	fflush(stdout);
	log_info("Allocating memory...");
	ytrv_vm_t *vm = ytrv_vm_init(true);
	log_info("Allocating memory SUCCESS");
	ytrv_vm_exec_single(vm, 0b11111111111111111000111110010011);
	log_info("Deallocating memory...");
	ytrv_vm_destroy(vm);
	log_info("Deallocating memory SUCCESS");
	puts("Press any key to exit...");
	getchar();
	fclose(log_file);
	return 0;
}
