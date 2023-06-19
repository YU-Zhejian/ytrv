#ifdef __cplusplus
extern "C"
{
#endif


#include "yuzj_tiny_riscv.h"

uint32_t ytrv_uint32_sub(uint32_t src_int, uint8_t from_pos, uint8_t to_pos)
{
	return (src_int >> from_pos) % (1 << (to_pos - from_pos));
}

uint32_t ytrv_get_msb(uint32_t src_num){
	uint32_t src_num_cp = src_num;
	uint32_t msb = 0;
	while(src_num_cp != 0){
		src_num_cp = src_num_cp >> 1;
		msb += 1;
	}
	return msb;
}

uint32_t ytrv_unsigned_to_signed(uint32_t src_num, bool is_positive){
	if (is_positive){
		if (ytrv_uint32_sub(src_num, 31, 32) == 1){
			// TODO: Except overflow
		}
		return src_num;
	} else{
		return ~src_num + 1;
	}
}

uint32_t ytrv_to_negative(uint32_t src_num){
	if ((src_num >> 31) == 0){ // Positive
		return ~src_num + 1;
	} else{
		return ~(src_num - 1);
	}
}

uint32_t ytrv_sign_extend(uint32_t src_num, uint8_t msb)
{
	// Number to extend; should be the highest position. 0 or 1.
	uint32_t extend_num = (src_num >> (msb - 1)) & 1;
	if (extend_num != 1)
	{ // Positive number, extend with 0. i.e., do nothing
		return src_num & (1 << (msb + 1)) - 1;
	}
	else
	{ // Negative number, extend with 1
		return src_num | (UINT32_MAX << msb);
	}
}

#ifdef __cplusplus
}
#endif