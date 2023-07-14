
#include "munit.h"
#include "ytrv/dev/dram.h"

inline static uint64_t idx_to_addr(uint64_t index){
	return YTRV_DEV_DRAM_BASE + index;
}

MunitResult test_ytrv_dram_uint8(const MunitParameter *ptr, void *pVoid)
{
	ytrv_dev_dram_t* ytrv_dev_dram = ytrv_dev_dram_init(128);
	ytrv_dev_dram_save_uint8(ytrv_dev_dram, idx_to_addr(11), 18);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),==, 18);
	ytrv_dev_dram_destroy(ytrv_dev_dram);
	return MUNIT_OK;
}

MunitResult test_ytrv_dram_uint16(const MunitParameter *ptr, void *pVoid)
{
	ytrv_dev_dram_t* ytrv_dev_dram = ytrv_dev_dram_init(128);
	ytrv_dev_dram_save_uint16(ytrv_dev_dram, idx_to_addr(11), 18);
	munit_assert_uint16(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(11)),==, 18);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),==, 18);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),==, 0);
	ytrv_dev_dram_save_uint16(ytrv_dev_dram, idx_to_addr(11), 0b000000100000101);
	munit_assert_uint16(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(11)),==, 0b000000100000101);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),==, 0b00000101);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),==, 0b0000001);
	ytrv_dev_dram_save_uint16(ytrv_dev_dram, idx_to_addr(11), UINT16_MAX);
	munit_assert_uint16(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(11)),==, UINT16_MAX);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),==, UINT8_MAX);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),==, UINT8_MAX);
	ytrv_dev_dram_destroy(ytrv_dev_dram);
	return MUNIT_OK;
}

MunitResult test_ytrv_dram_uint32(const MunitParameter *ptr, void *pVoid)
{
	ytrv_dev_dram_t* ytrv_dev_dram = ytrv_dev_dram_init(128);
	ytrv_dev_dram_save_uint32(ytrv_dev_dram, idx_to_addr(11), 18);
	munit_assert_uint32(ytrv_dev_dram_load_uint32(ytrv_dev_dram, idx_to_addr(11)),==, 18);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),==, 18);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),==, 0);
	ytrv_dev_dram_save_uint32(ytrv_dev_dram, idx_to_addr(11), 0b000000100000101);
	munit_assert_uint32(ytrv_dev_dram_load_uint32(ytrv_dev_dram, idx_to_addr(11)),==, 0b000000100000101);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),==, 0b00000101);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),==, 0b0000001);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(13)),==, 0);
	munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(14)),==, 0);

	ytrv_dev_dram_save_uint32(ytrv_dev_dram, idx_to_addr(11), UINT32_MAX);
	munit_assert_uint32(ytrv_dev_dram_load_uint32(ytrv_dev_dram, idx_to_addr(11)),==, UINT32_MAX);
	for (int i = 11; i< 15; i++){
		munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(i)),==, UINT8_MAX);
	}
	for (int i = 11; i< 15; i+=2){
		munit_assert_uint16(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(i)),==, UINT16_MAX);
	}
	ytrv_dev_dram_destroy(ytrv_dev_dram);
	return MUNIT_OK;
}

MunitResult test_ytrv_dram_uint64(const MunitParameter *ptr, void *pVoid)
{
	ytrv_dev_dram_t* ytrv_dev_dram = ytrv_dev_dram_init(128);
	ytrv_dev_dram_save_uint64(ytrv_dev_dram, idx_to_addr(11), UINT64_MAX);
	munit_assert_uint64(ytrv_dev_dram_load_uint64(ytrv_dev_dram, idx_to_addr(11)),==, UINT64_MAX);
	for (int i = 11; i< 19; i++){
		munit_assert_uint8(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(i)),==, UINT8_MAX);
	}
	for (int i = 11; i< 19; i+=2){
		munit_assert_uint16(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(i)),==, UINT16_MAX);
	}
	for (int i = 11; i< 19; i+=4){
		munit_assert_uint32(ytrv_dev_dram_load_uint32(ytrv_dev_dram, idx_to_addr(i)),==, UINT16_MAX);
	}
	ytrv_dev_dram_destroy(ytrv_dev_dram);
	return MUNIT_OK;
}
MunitTest tests[] = {
	{
		"/test_ytrv_dram_uint8",
		test_ytrv_dram_uint8,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_ytrv_dram_uint16",
		test_ytrv_dram_uint16,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_ytrv_dram_uint32",
		test_ytrv_dram_uint32,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	{
		"/test_ytrv_dram_uint64",
		test_ytrv_dram_uint64,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	},
	// Last item that should be placed due to its documentation
	{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {
	"/test_dev_dram", /* name */
	tests, /* tests */
	NULL, /* suites */
	1, /* iterations */
	MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
	return munit_suite_main(&test_suite, NULL, argc, argv);
}
