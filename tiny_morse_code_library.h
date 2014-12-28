#ifndef __TYNY_MORSE_CODE_LIBRARY_H_INCLUDED__
#define __TYNY_MORSE_CODE_LIBRARY_H_INCLUDED__

#include <stdint.h>

#define M_N (0x00)
#define M_O (0x01)
#define M_A (0x02)

	struct morse_flat_t {
		uint8_t t[8];
	};

	_Bool morse_char_to_flat (const char c, struct morse_flat_t *st);

#endif /* __TYNY_MORSE_CODE_LIBRARY_H_INCLUDED__ */
