#include <ceu_check/ceu_check_all.h>

int main()
{
	char* cbuff = get_full_info();
	printf("%s\n", cbuff);
	ceu_free_non_null(cbuff);
	puts("Press any key to exit...");
	getchar();
	return 0;
}
