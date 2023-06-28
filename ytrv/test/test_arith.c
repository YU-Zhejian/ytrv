#include <munit.h>
#include "ytrv/arith.h"

MunitResult test_ytrv_uint32_sub(const MunitParameter *ptr, void *pVoid)
{
	munit_assert_uint32(ytrv_uint32_sub(0b00000000101010101111111111111111, 16, 25), ==, 0b10101010);
	return MUNIT_OK;
}

MunitResult test_binary_representation(const MunitParameter *ptr, void *pVoid)
{
	munit_assert_uint32(0b00000000000000000000000000001111, ==, 15);
	munit_assert_uint32(0b00000000000000000000000011110000, ==, 15 << 4);
	munit_assert_uint32(0b00000000000000000000000011110000 >> 4, ==, 15);
	munit_assert_uint32(15 >> 12, ==, 0);
	munit_assert_uint32(0x000000f, ==, 15);
	return MUNIT_OK;
}

MunitResult test_ytrv_get_msb(const MunitParameter *ptr, void *pVoid)
{
	munit_assert_uint32(ytrv_get_msb(15), ==, 4); // 15 = 2^4 - 1
	munit_assert_uint32(ytrv_get_msb(16), ==, 5); // 15 = 2^4 - 1
	return MUNIT_OK;
}

MunitResult test_ytrv_unsigned_to_signed(const MunitParameter *ptr, void *pVoid)
{
	munit_assert_uint32(ytrv_signed_to_encoded_unsigned(15), ==, 15);
	munit_assert_uint32(ytrv_signed_to_encoded_unsigned(-15), ==, 0b11111111111111111111111111110001);
	munit_assert_uint32(ytrv_signed_to_encoded_unsigned(16), ==, 16);
	munit_assert_uint32(ytrv_signed_to_encoded_unsigned(-16), ==, 0b11111111111111111111111111110000);

	munit_assert_uint32(ytrv_encoded_unsigned_to_signed(15), ==, 15);
	munit_assert_uint32(ytrv_encoded_unsigned_to_signed(0b11111111111111111111111111110001), ==, -15);
	munit_assert_uint32(ytrv_encoded_unsigned_to_signed(16), ==, 16);
	munit_assert_uint32(ytrv_encoded_unsigned_to_signed(0b11111111111111111111111111110000), ==, -16);

	return MUNIT_OK;
}

MunitResult test_ytrv_sign_extend(const MunitParameter *ptr, void *pVoid)
{
	munit_assert_uint32(ytrv_sign_extend(0b00000000000000000000010000010010, 12), ==,
						0b00000000000000000000010000010010);
	munit_assert_uint32(ytrv_sign_extend(0b00000000000000000001000000010010, 12), ==,
						0b00000000000000000001000000010010);
	munit_assert_uint32(ytrv_sign_extend(0b00000000001000000000000000010010, 12), ==,
						0b00000000000000000000000000010010);
	munit_assert_uint32(ytrv_sign_extend(0b00000000000000000000100000010010, 12), ==,
						0b11111111111111111111100000010010);
	return MUNIT_OK;
}

MunitResult test_ytrv_to_negative(const MunitParameter *ptr, void *pVoid)
{
	munit_assert_uint32(ytrv_to_negative(15), ==, 0b11111111111111111111111111110001);
	munit_assert_uint32(ytrv_to_negative(0b11111111111111111111111111110001), ==, 15);
	return MUNIT_OK;
}

MunitTest tests[] = {
	{
		"/test_binary_representation",
		test_binary_representation,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_ytrv_uint32_sub",
		test_ytrv_uint32_sub,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_ytrv_to_negative",
		test_ytrv_to_negative,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_ytrv_get_msb",
		test_ytrv_get_msb,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_ytrv_unsigned_to_signed",
		test_ytrv_unsigned_to_signed,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_ytrv_sign_extend",
		test_ytrv_sign_extend,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	// Last item that should be placed due to its documentation
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {
	"/test_arith", /* name */
	tests, /* tests */
	NULL, /* suites */
	1, /* iterations */
	MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
	return munit_suite_main(&test_suite, NULL, argc, argv);
}
