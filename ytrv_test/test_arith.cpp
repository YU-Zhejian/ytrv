#include <gtest/gtest.h>
#include "ytrv/arith.h"

TEST(test_ytrv_uint32_sub, test_arith)
{
	ASSERT_EQ(ytrv_uint32_sub(0b00000000101010101111111111111111, 16, 25),  0b10101010);
}

TEST(test_binary_representation, test_arith)
{
	ASSERT_EQ(0b00000000000000000000000000001111,  15);
	ASSERT_EQ(0b00000000000000000000000011110000,  15 << 4);
	ASSERT_EQ(0b00000000000000000000000011110000 >> 4,  15);
	ASSERT_EQ(15 >> 12,  0);
	ASSERT_EQ(0x000000f,  15);
}

TEST(test_ytrv_get_msb, test_arith)
{
	ASSERT_EQ(ytrv_get_msb(15),  4); // 15 = 2^4 - 1
	ASSERT_EQ(ytrv_get_msb(16),  5); // 15 = 2^4 - 1
}

TEST(test_ytrv_unsigned_to_signed, test_arith)
{
	ASSERT_EQ(ytrv_signed_to_encoded_unsigned(15),  15);
	ASSERT_EQ(ytrv_signed_to_encoded_unsigned(-15),  0b11111111111111111111111111110001);
	ASSERT_EQ(ytrv_signed_to_encoded_unsigned(16),  16);
	ASSERT_EQ(ytrv_signed_to_encoded_unsigned(-16),  0b11111111111111111111111111110000);

	ASSERT_EQ(ytrv_encoded_unsigned_to_signed(15),  15);
	ASSERT_EQ(ytrv_encoded_unsigned_to_signed(0b11111111111111111111111111110001),  -15);
	ASSERT_EQ(ytrv_encoded_unsigned_to_signed(16),  16);
	ASSERT_EQ(ytrv_encoded_unsigned_to_signed(0b11111111111111111111111111110000),  -16);

}

TEST(test_ytrv_sign_extend, test_arith)
{
	ASSERT_EQ(ytrv_sign_extend(0b00000000000000000000010000010010, 12), 
						0b00000000000000000000010000010010);
	ASSERT_EQ(ytrv_sign_extend(0b00000000000000000001000000010010, 12), 
						0b00000000000000000001000000010010);
	ASSERT_EQ(ytrv_sign_extend(0b00000000001000000000000000010010, 12), 
						0b00000000000000000000000000010010);
	ASSERT_EQ(ytrv_sign_extend(0b00000000000000000000100000010010, 12), 
						0b11111111111111111111100000010010);
}

TEST(test_ytrv_to_negative, test_arith)
{
	ASSERT_EQ(ytrv_to_negative(15),  0b11111111111111111111111111110001);
	ASSERT_EQ(ytrv_to_negative(0b11111111111111111111111111110001),  15);
}
