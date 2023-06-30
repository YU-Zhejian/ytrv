#include "munit.h"
#include "ytrv/op.h"
#include "ytrv/arith.h"


MunitResult test_addi()
{
	uint32_t max_uint32 = 4294967295;  // (1<<32) - 1; represents -1 in signed int32

	ytrv_vm_t *vm = ytrv_vm_init(0);
	// Normal condition
	vm->x[1] = 1;
	ytrv_op_addi(vm, 1, 2, 15);
	munit_assert_int32(vm->x[2], ==, 16);

	// Overflow
	vm->x[1] = max_uint32;
	ytrv_op_addi(vm, 1, 2, 25);
	munit_assert_int32(vm->x[2], ==, 24);

	// Negative number
	vm->x[1] = -32;
	ytrv_op_addi(vm, 1, 2, 34);
	munit_assert_int32(vm->x[2], ==, 2);

	// Negative number
	vm->x[1] = 34;
	ytrv_op_addi(vm, 1, 2, -32);
	munit_assert_int32(vm->x[2], ==, 2);

	// Negative number
	vm->x[1] = 32;
	ytrv_op_addi(vm, 1, 2, -34);
	munit_assert_int32(vm->x[2], ==, -2);

	ytrv_vm_destroy(vm);
	return MUNIT_OK;
}

MunitResult test_slti()
{
	ytrv_vm_t *vm = ytrv_vm_init(0);
	vm->x[1] = 1;
	ytrv_op_slti(vm, 1, 2, 0);
	munit_assert_uint32(vm->x[2], ==, 0);

	vm->x[1] = 1;
	ytrv_op_slti(vm, 1, 2, 1);
	munit_assert_uint32(vm->x[2], ==, 0);

	vm->x[1] = 1;
	ytrv_op_slti(vm, 1, 2, 2);
	munit_assert_uint32(vm->x[2], ==, 1);

	// Negative number

	vm->x[1] = 1;
	ytrv_op_slti(vm, 1, 2, (uint32_t)-5);
	munit_assert_uint32(vm->x[2], ==, 0);


	vm->x[1] = (uint32_t)-1;
	ytrv_op_slti(vm, 1, 2, (uint32_t)-5);
	munit_assert_uint32(vm->x[2], ==, 0);

	vm->x[1] = (uint32_t)-5;
	ytrv_op_slti(vm, 1, 2, (uint32_t)-5);
	munit_assert_uint32(vm->x[2], ==, 0);

	vm->x[1] = (uint32_t)-8;
	ytrv_op_slti(vm, 1, 2, (uint32_t)-5);
	munit_assert_uint32(vm->x[2], ==, 1);

	ytrv_vm_destroy(vm);
	return MUNIT_OK;
}

MunitResult test_sltiu()
{
	ytrv_vm_t *vm = ytrv_vm_init(0);
	vm->x[1] = 1;
	ytrv_op_sltiu(vm, 1, 2, 0);
	munit_assert_uint32(vm->x[2], ==, 0);

	vm->x[1] = 1;
	ytrv_op_sltiu(vm, 1, 2, 1);
	munit_assert_uint32(vm->x[2], ==, 0);

	vm->x[1] = 1;
	ytrv_op_sltiu(vm, 1, 2, 2);
	munit_assert_uint32(vm->x[2], ==, 1);

	// Negative number

	vm->x[1] = 1;
	ytrv_op_sltiu(vm, 1, 2, (uint32_t)-5); // Larger
	munit_assert_uint32(vm->x[2], ==, 1);

	vm->x[1] = (uint32_t)-1; // Larger
	ytrv_op_sltiu(vm, 1, 2, (uint32_t)-5);
	munit_assert_uint32(vm->x[2], ==, 0);

	vm->x[1] = (uint32_t)-5;
	ytrv_op_sltiu(vm, 1, 2, (uint32_t)-5);
	munit_assert_uint32(vm->x[2], ==, 0);

	vm->x[1] = (uint32_t)-8;
	ytrv_op_sltiu(vm, 1, 2, (uint32_t)-5);
	munit_assert_uint32(vm->x[2], ==, 1);

	ytrv_vm_destroy(vm);
	return MUNIT_OK;
}

MunitTest tests[] = {
	{
		"/test_addi",
		test_addi,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_slti",
		test_slti,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_sltiu",
		test_sltiu,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	// Last item that should be placed due to its documentation
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {
	"/test_vm", /* name */
	tests, /* tests */
	NULL, /* suites */
	1, /* iterations */
	MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
	return munit_suite_main(&test_suite, NULL, argc, argv);
}
