#include <stdint.h>
#include "tiny_morse_code_library.h"


#define M8(T1, T2, T3, T4) ((uint8_t)((M_ ## T1 << 0) | (M_ ## T2 << 2) | (M_ ## T3 << 4) | (M_ ## T4 << 6)))
#define M16(T1, T2, T3, T4, T5, T6, T7, T8) ((uint16_t)(M8(T1, T2, T3, T4) | (M_ ## T5 << 8) | (M_ ## T6 << 10) | (M_ ## T7 << 12) | (M_ ## T8 << 14)))


static
uint8_t
morse_alpha['z' - 'a' + 1] = {
	M8(O, A, N, N),
	M8(A, O, O, O),
	M8(A, O, A, O),
	M8(A, O, O, N),
	M8(O, N, N, N),
	M8(O, O, A, O),
	M8(A, A, O, N),
	M8(O, O, O, O),
	M8(O, O, N, N),
	M8(O, A, A, A),
	M8(A, O, A, N),
	M8(O, A, O, O),
	M8(A, A, N, N),
	M8(A, O, N, N),
	M8(A, A, A, N),
	M8(O, A, A, O),
	M8(A, A, O, A),
	M8(O, A, O, N),
	M8(O, O, O, N),
	M8(A, N, N, N),
	M8(O, O, A, N),
	M8(O, O, O, A),
	M8(O, A, A, N),
	M8(A, O, O, A),
	M8(A, O, A, A),
	M8(A, A, O, O)
};

static
uint16_t
morse_digit['9' - '0' + 1] = {
	M16(A, A, A, A, A, N, N, N),
	M16(O, A, A, A, A, N, N, N),
	M16(O, O, A, A, A, N, N, N),
	M16(O, O, O, A, A, N, N, N),
	M16(O, O, O, O, A, N, N, N),
	M16(O, O, O, O, O, N, N, N),
	M16(A, O, O, O, O, N, N, N),
	M16(A, A, O, O, O, N, N, N),
	M16(A, A, A, O, O, N, N, N),
	M16(A, A, A, A, O, N, N, N)
};


static void morse_entry8_to_flat (uint8_t entry, struct morse_flat_t *st);
static void morse_entry16_to_flat (uint16_t entry, struct morse_flat_t *st);


_Bool
morse_char_to_flat (const char c, struct morse_flat_t *st)
{
	_Bool not_matched = 0;

	if ((c >= 'a') && (c <= 'z'))
		morse_entry8_to_flat(morse_alpha[c - 'a'], st);
	else if ((c >= 'A') && (c <= 'Z'))
		morse_entry8_to_flat(morse_alpha[c - 'A'], st);
	else if ((c >= '0') && (c <= '9'))
		morse_entry16_to_flat(morse_digit[c - '0'], st);
	else {
		switch (c) {
			case '!':
				morse_entry16_to_flat(M16(A, O, A, O, A, A, N, N), st);
				break;
			case '(':
				morse_entry16_to_flat(M16(A, O, A, A, O, N, N, N), st);
				break;
			case ')':
				morse_entry16_to_flat(M16(A, O, A, A, O, A, N, N), st);
				break;
			case ',':
				morse_entry16_to_flat(M16(A, A, O, O, A, A, N, N), st);
				break;
			case '-':
				morse_entry16_to_flat(M16(A, O, O, O, O, A, N, N), st);
				break;
			case '.':
				morse_entry16_to_flat(M16(O, A, O, A, O, A, N, N), st);
				break;
			case '/':
				morse_entry16_to_flat(M16(A, O, O, A, O, N, N, N), st);
				break;
			case '?':
				morse_entry16_to_flat(M16(O, O, A, A, O, O, N, N), st);
				break;
			case '@':
				morse_entry16_to_flat(M16(O, A, A, O, A, O, N, N), st);
				break;
			default:
				not_matched = !0;
				break;
		}
	}

	return not_matched;
}

static
void
morse_entry8_to_flat (uint8_t entry, struct morse_flat_t *st)
{
	int i;

	for (i=0; i<4; i++, entry>>=2)
		st->t[i] = entry & 0x03;
	for (i=4; i<8; i++)
		st->t[i] = M_N;
	
	return;
}

static
void
morse_entry16_to_flat (uint16_t entry, struct morse_flat_t *st)
{
	int i;

	for (i=0; i<8; i++, entry>>=2)
		st->t[i] = entry & 0x03;
	
	return;
}
