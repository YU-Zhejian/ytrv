#include <gtest/gtest.h>

#include "ytrv/dev/dram.h"

inline static uint64_t idx_to_addr(uint64_t index){
	return YTRV_DEV_DRAM_BASE + index;
}

TEST (test_ytrv_dram_uint8, test_dev_dram)
{
	ytrv_dev_dram_t* ytrv_dev_dram = ytrv_dev_dram_init(128);
	ytrv_dev_dram_save_uint8(ytrv_dev_dram, idx_to_addr(11), 18);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),  18);
	ytrv_dev_dram_destroy(ytrv_dev_dram);
}

TEST (test_ytrv_dram_uint16, test_dev_dram)
{
	ytrv_dev_dram_t* ytrv_dev_dram = ytrv_dev_dram_init(128);
	ytrv_dev_dram_save_uint16(ytrv_dev_dram, idx_to_addr(11), 18);
	ASSERT_EQ(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(11)),  18);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),  18);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),  0);
	ytrv_dev_dram_save_uint16(ytrv_dev_dram, idx_to_addr(11), 0b000000100000101);
	ASSERT_EQ(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(11)),  0b000000100000101);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),  0b00000101);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),  0b0000001);
	ytrv_dev_dram_save_uint16(ytrv_dev_dram, idx_to_addr(11), UINT16_MAX);
	ASSERT_EQ(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(11)),  UINT16_MAX);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),  UINT8_MAX);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),  UINT8_MAX);
	ytrv_dev_dram_destroy(ytrv_dev_dram);
}

TEST (test_ytrv_dram_uint32, test_dev_dram)
{
	ytrv_dev_dram_t* ytrv_dev_dram = ytrv_dev_dram_init(128);
	ytrv_dev_dram_save_uint32(ytrv_dev_dram, idx_to_addr(11), 18);
	ASSERT_EQ(ytrv_dev_dram_load_uint32(ytrv_dev_dram, idx_to_addr(11)),  18);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),  18);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),  0);
	ytrv_dev_dram_save_uint32(ytrv_dev_dram, idx_to_addr(11), 0b000000100000101);
	ASSERT_EQ(ytrv_dev_dram_load_uint32(ytrv_dev_dram, idx_to_addr(11)),  0b000000100000101);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(11)),  0b00000101);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(12)),  0b0000001);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(13)),  0);
	ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(14)),  0);

	ytrv_dev_dram_save_uint32(ytrv_dev_dram, idx_to_addr(11), UINT32_MAX);
	ASSERT_EQ(ytrv_dev_dram_load_uint32(ytrv_dev_dram, idx_to_addr(11)),  UINT32_MAX);
	for (int i = 11; i< 15; i++){
		ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(i)),  UINT8_MAX);
	}
	for (int i = 11; i< 15; i+=2){
		ASSERT_EQ(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(i)),  UINT16_MAX);
	}
	ytrv_dev_dram_destroy(ytrv_dev_dram);
}

TEST (test_ytrv_dram_uint64, test_dev_dram)
{
	ytrv_dev_dram_t* ytrv_dev_dram = ytrv_dev_dram_init(128);
	ytrv_dev_dram_save_uint64(ytrv_dev_dram, idx_to_addr(11), UINT64_MAX);
	ASSERT_EQ(ytrv_dev_dram_load_uint64(ytrv_dev_dram, idx_to_addr(11)),  UINT64_MAX);
	for (int i = 11; i< 19; i++){
		ASSERT_EQ(ytrv_dev_dram_load_uint8(ytrv_dev_dram, idx_to_addr(i)),  UINT8_MAX);
	}
	for (int i = 11; i< 19; i+=2){
		ASSERT_EQ(ytrv_dev_dram_load_uint16(ytrv_dev_dram, idx_to_addr(i)),  UINT16_MAX);
	}
	for (int i = 11; i< 19; i+=4){
		ASSERT_EQ(ytrv_dev_dram_load_uint32(ytrv_dev_dram, idx_to_addr(i)),  UINT16_MAX);
	}
	ytrv_dev_dram_destroy(ytrv_dev_dram);
}
