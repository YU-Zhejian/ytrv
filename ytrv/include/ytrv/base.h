/**
 * YTRV base specifications.
 */

#ifndef YUZJ_TINY_RISCV_BASE_H
#define YUZJ_TINY_RISCV_BASE_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

/*!
 * Check whether the compiler infrastructure is YTRV-compliant. That includes:
 *
 * - 2-based complementary in int <-> uint conversions.
 * - true == 1, false == 0.
 */
static inline void ytrv_compiler_check(void)
{
	volatile uint32_t a = 4294967295;
	volatile int32_t b = -1;
	volatile uint32_t c = 1;
	volatile int32_t d = 1;
	volatile uint32_t e = -1;
	assert(a == (uint32_t)b);
	assert(a == e);
	assert(c == d);
	assert((uint32_t)true == 1);
	assert((uint32_t)false == 0);
}

static const char *YTRV_VERSION = "0.0.1";

#endif // YUZJ_TINY_RISCV_BASE_H
