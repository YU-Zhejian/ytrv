#ifndef YUZJ_TINY_RISCV_ARITH_H
#define YUZJ_TINY_RISCV_ARITH_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

uint32_t ytrv_uint32_sub(uint32_t src_int, uint8_t from_pos, uint8_t to_pos);

uint32_t ytrv_sign_extend(uint32_t src_num, uint8_t msb);

/*!
 * Convert signed int32 number to encoded unsigned int32.
 *
 * @param src_num The source number.
 * @return Converted number. Would set highest bits to 1 for negative numbers.
 */
uint32_t ytrv_signed_to_encoded_unsigned(int32_t src_num);

/*!
 * Convert encoded unsigned int32 to signed one.
 *
 * @param src_num The source number.
 * @return Converted number.
 */
int32_t ytrv_encoded_unsigned_to_signed(uint32_t src_num);

uint32_t ytrv_get_msb(uint32_t src_num);

uint32_t ytrv_to_negative(uint32_t src_num);

#ifdef __cplusplus
}
#endif

#endif //YUZJ_TINY_RISCV_ARITH_H
