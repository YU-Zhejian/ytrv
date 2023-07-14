#include <gtest/gtest.h>

#include "ytrv/op.h"

TEST(test_addi, test_op)
{
	uint32_t max_uint32 = 4294967295;  // (1<<32) - 1; represents -1 in signed int32

	ytrv_vm_t *vm = ytrv_vm_init(0);
	// Normal condition
	vm->x[1] = 1;
	ytrv_op_addi(vm, 1, 2, 15);
	ASSERT_EQ(vm->x[2], 16);

	// Overflow
	vm->x[1] = max_uint32;
	ytrv_op_addi(vm, 1, 2, 25);
	ASSERT_EQ(vm->x[2], 24);

	// Negative number
	vm->x[1] = -32;
	ytrv_op_addi(vm, 1, 2, 34);
	ASSERT_EQ(vm->x[2], 2);

	// Negative number
	vm->x[1] = 34;
	ytrv_op_addi(vm, 1, 2, -32);
	ASSERT_EQ(vm->x[2], 2);

	// Negative number
	vm->x[1] = 32;
	ytrv_op_addi(vm, 1, 2, -34);
	ASSERT_EQ(vm->x[2], -2);

	ytrv_vm_destroy(vm);
}


TEST(test_slti, test_op)
{
	ytrv_vm_t *vm = ytrv_vm_init(0);
	vm->x[1] = 1;
	ytrv_op_slti(vm, 1, 2, 0);
	ASSERT_EQ(vm->x[2], 0);

	vm->x[1] = 1;
	ytrv_op_slti(vm, 1, 2, 1);
	ASSERT_EQ(vm->x[2], 0);

	vm->x[1] = 1;
	ytrv_op_slti(vm, 1, 2, 2);
	ASSERT_EQ(vm->x[2], 1);

	// Negative number

	vm->x[1] = 1;
	ytrv_op_slti(vm, 1, 2, (uint32_t)-5);
	ASSERT_EQ(vm->x[2], 0);


	vm->x[1] = (uint32_t)-1;
	ytrv_op_slti(vm, 1, 2, (uint32_t)-5);
	ASSERT_EQ(vm->x[2], 0);

	vm->x[1] = (uint32_t)-5;
	ytrv_op_slti(vm, 1, 2, (uint32_t)-5);
	ASSERT_EQ(vm->x[2], 0);

	vm->x[1] = (uint32_t)-8;
	ytrv_op_slti(vm, 1, 2, (uint32_t)-5);
	ASSERT_EQ(vm->x[2], 1);

	ytrv_vm_destroy(vm);

}
	TEST(test_sltiu, test_op)
{
	ytrv_vm_t *vm = ytrv_vm_init(0);
	vm->x[1] = 1;
	ytrv_op_sltiu(vm, 1, 2, 0);
	ASSERT_EQ(vm->x[2], 0);

	vm->x[1] = 1;
	ytrv_op_sltiu(vm, 1, 2, 1);
	ASSERT_EQ(vm->x[2], 0);

	vm->x[1] = 1;
	ytrv_op_sltiu(vm, 1, 2, 2);
	ASSERT_EQ(vm->x[2], 1);

	// Negative number

	vm->x[1] = 1;
	ytrv_op_sltiu(vm, 1, 2, (uint32_t)-5); // Larger
	ASSERT_EQ(vm->x[2], 1);

	vm->x[1] = (uint32_t)-1; // Larger
	ytrv_op_sltiu(vm, 1, 2, (uint32_t)-5);
	ASSERT_EQ(vm->x[2], 0);

	vm->x[1] = (uint32_t)-5;
	ytrv_op_sltiu(vm, 1, 2, (uint32_t)-5);
	ASSERT_EQ(vm->x[2], 0);

	vm->x[1] = (uint32_t)-8;
	ytrv_op_sltiu(vm, 1, 2, (uint32_t)-5);
	ASSERT_EQ(vm->x[2], 1);

	ytrv_vm_destroy(vm);
}
