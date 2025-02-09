#include <stdio.h>
#include "ceu_c_utils.h"
#include "ceu_check/ceu_check_all.h"
#include "log.h"

#include "ytrv/vm.h"


static inline void print_version_info()
{
	char *cbuff = ceu_check_get_full_info();
	printf("%s\n", cbuff);
	printf("log.c version %s\n", LOG_VERSION);
	ceu_free_non_null(cbuff);
}

int main(int argc, char **argv)
{
	log_set_level(LOG_INFO);
	FILE *log_file = fopen("log.log", "w");
	if (log_file == NULL) {
		ceu_die_with_retv("Cannot open log!", 1);
	}
	log_add_fp(log_file, LOG_TRACE);
	log_info("YUZJ TINY RISCV RV32I VM");
	// log_info("Version info");
	// print_version_info();
	fflush(stdout);
	ytrv_vm_t *vm = ytrv_vm_init(1024 * 1024); // 1 mega bytes
	ytrv_vm_loadbin(vm, argv[1]);
	ytrv_vm_exec(vm);
	log_info("Deallocating memory...");
	ytrv_vm_destroy(vm);
	log_info("Deallocating memory SUCCESS");
	puts("Press any key to exit...");
	getchar();
	fclose(log_file);
	log_file = NULL;
	return 0;
}
