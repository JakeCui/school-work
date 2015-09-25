#include "RoundEngine.h"

ull r_runRounds(ull in, ull keys[16])
{
	// rounds
	ull l = (in & 0xFFFFFFFF00000000ULL);
	ull r = (in & 0x00000000FFFFFFFFULL) << 32;
	for (int round = 1; round <= 16; round++)
	{
		ull rOld = r;

		// expansion of right half
		r = r_pExpansion(r);

		// mix in key
		r ^= keys[round - 1];

		// split into s-box blocks
		ush b1 = (r & 0xfc00000000000000ULL) >> (42 + 16);
		ush b2 = (r & 0x03f0000000000000ULL) >> (36 + 16);
		ush b3 = (r & 0x000fc00000000000ULL) >> (30 + 16);
		ush b4 = (r & 0x00003f0000000000ULL) >> (24 + 16);
		ush b5 = (r & 0x000000fc00000000ULL) >> (18 + 16);
		ush b6 = (r & 0x00000003f0000000ULL) >> (12 + 16);
		ush b7 = (r & 0x000000000fc00000ULL) >> (6 + 16);
		ush b8 = (r & 0x00000000003f0000ULL) >> (0 + 16);
		r = 0;
		r = (r | r_sBox(b1, 0)) << 4;
		r = (r | r_sBox(b2, 1)) << 4;
		r = (r | r_sBox(b3, 2)) << 4;
		r = (r | r_sBox(b4, 3)) << 4;
		r = (r | r_sBox(b5, 4)) << 4;
		r = (r | r_sBox(b6, 5)) << 4;
		r = (r | r_sBox(b7, 6)) << 4;
		r = (r | r_sBox(b8, 7));
		r <<= 32;

		// post s-box straight p-box
		r = r_pStraight(r);

		// xor with left half
		r ^= l;

		// old R becomes new L
		l = rOld;
	}

	return (r | (l >> 32));
}

ull r_pExpansion(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbits(out, 2, 48);
	if (bitset(in, 2)) out |= setbit(out, 3);
	if (bitset(in, 3)) out |= setbit(out, 4);
	if (bitset(in, 4)) out |= setbits(out, 5, 7);
	if (bitset(in, 5)) out |= setbits(out, 6, 8);
	if (bitset(in, 6)) out |= setbit(out, 9);
	if (bitset(in, 7)) out |= setbit(out, 10);
	if (bitset(in, 8)) out |= setbits(out, 11, 13);
	if (bitset(in, 9)) out |= setbits(out, 12, 14);
	if (bitset(in, 10)) out |= setbit(out, 15);
	if (bitset(in, 11)) out |= setbit(out, 16);
	if (bitset(in, 12)) out |= setbits(out, 17, 19);
	if (bitset(in, 13)) out |= setbits(out, 18, 20);
	if (bitset(in, 14)) out |= setbit(out, 21);
	if (bitset(in, 15)) out |= setbit(out, 22);
	if (bitset(in, 16)) out |= setbits(out, 23, 25);
	if (bitset(in, 17)) out |= setbits(out, 24, 26);
	if (bitset(in, 18)) out |= setbit(out, 27);
	if (bitset(in, 19)) out |= setbit(out, 28);
	if (bitset(in, 20)) out |= setbits(out, 29, 31);
	if (bitset(in, 21)) out |= setbits(out, 30, 32);
	if (bitset(in, 22)) out |= setbit(out, 33);
	if (bitset(in, 23)) out |= setbit(out, 34);
	if (bitset(in, 24)) out |= setbits(out, 35, 37);
	if (bitset(in, 25)) out |= setbits(out, 36, 38);
	if (bitset(in, 26)) out |= setbit(out, 39);
	if (bitset(in, 27)) out |= setbit(out, 40);
	if (bitset(in, 28)) out |= setbits(out, 41, 43);
	if (bitset(in, 29)) out |= setbits(out, 42, 44);
	if (bitset(in, 30)) out |= setbit(out, 45);
	if (bitset(in, 31)) out |= setbit(out, 46);
	if (bitset(in, 32)) out |= setbits(out, 47, 1);

	return out;
}

ush r_sBoxes[8][64] = {
	// S1
	{ 
		14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
	},
	// S2
	{
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
	},
	// S3
	{
		10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
	},
	// S4
	{
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
	},
	// S5
	{
		2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
	},
	// S6
	{
		12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 10, 0, 8, 13
	},
	// S7
	{
		4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
	},
	// S8
	{
		13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
		//1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 10, 14, 9, 2,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
	}
};

ush r_sBox(ush in, ush box)
{
	ush b1 = (in & 0x20) >> 5;
	ush b6 = (in & 0x1);
	ush b16 = (b1 << 1) | b6;
	ush b2345 = (in >> 1) & 0xf;

	ush b = (b16 << 4) | b2345;

	return r_sBoxes[box][b];
}

ull r_pStraight(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbit(out, 9);
	if (bitset(in, 2)) out |= setbit(out, 17);
	if (bitset(in, 3)) out |= setbit(out, 23);
	if (bitset(in, 4)) out |= setbit(out, 31);
	if (bitset(in, 5)) out |= setbit(out, 13);
	if (bitset(in, 6)) out |= setbit(out, 28);
	if (bitset(in, 7)) out |= setbit(out, 2);
	if (bitset(in, 8)) out |= setbit(out, 18);
	if (bitset(in, 9)) out |= setbit(out, 24);
	if (bitset(in, 10)) out |= setbit(out, 16);
	if (bitset(in, 11)) out |= setbit(out, 30);
	if (bitset(in, 12)) out |= setbit(out, 6);
	if (bitset(in, 13)) out |= setbit(out, 26);
	if (bitset(in, 14)) out |= setbit(out, 20);
	if (bitset(in, 15)) out |= setbit(out, 10);
	if (bitset(in, 16)) out |= setbit(out, 1);
	if (bitset(in, 17)) out |= setbit(out, 8);
	if (bitset(in, 18)) out |= setbit(out, 14);
	if (bitset(in, 19)) out |= setbit(out, 25);
	if (bitset(in, 20)) out |= setbit(out, 3);
	if (bitset(in, 21)) out |= setbit(out, 4);
	if (bitset(in, 22)) out |= setbit(out, 29);
	if (bitset(in, 23)) out |= setbit(out, 11);
	if (bitset(in, 24)) out |= setbit(out, 19);
	if (bitset(in, 25)) out |= setbit(out, 32);
	if (bitset(in, 26)) out |= setbit(out, 12);
	if (bitset(in, 27)) out |= setbit(out, 22);
	if (bitset(in, 28)) out |= setbit(out, 7);
	if (bitset(in, 29)) out |= setbit(out, 5);
	if (bitset(in, 30)) out |= setbit(out, 27);
	if (bitset(in, 31)) out |= setbit(out, 15);
	if (bitset(in, 32)) out |= setbit(out, 21);

	return out;
}