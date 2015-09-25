#include "Common.h"
#include "KeyGenerator.h"
#include "RoundEngine.h"

// function declarations
ull EncodeBlock(ull key, ull in);
ull pInitial(ull n);
ull pFinal(ull n);

int main()
{
	// Forouzan text
	ull key = 0xAABB09182736CCDDULL;
	ull block = 0x123456ABCD132536ULL;
		
	// DES Algorithm Illustrated
	//ull key = 0x133457799BBCDFF1ULL;
	//ull block = 0x0123456789ABCDEFULL;

	// Reverse - Forouzan
	//ull key = 0xAABB09182736CCDDULL;
	//ull block = 0xc0b7a8d05f3a829cULL;

	ull result = EncodeBlock(key, block);

	return 0;
}

ull DESBlock(ull key, ull block)
{
	// generate round keys (48-bit)
	ull keys[16];
	kg_generate(key, keys, false);

	// initial permutation
	block = pInitial(block);

	// rounds
	block = r_runRounds(block, keys);

	// final permutation
	block = pFinal(block);

	return block;
}

#pragma region P-Boxes
ull pInitial(ull in)
{
	ull out = 0;
	
	if (bitset(in, 1)) out |= setbit(out, 40);
	if (bitset(in, 2)) out |= setbit(out, 8);
	if (bitset(in, 3)) out |= setbit(out, 48);
	if (bitset(in, 4)) out |= setbit(out, 16);
	if (bitset(in, 5)) out |= setbit(out, 56);
	if (bitset(in, 6)) out |= setbit(out, 24);
	if (bitset(in, 7)) out |= setbit(out, 64);
	if (bitset(in, 8)) out |= setbit(out, 32);
	if (bitset(in, 9)) out |= setbit(out, 39);
	if (bitset(in, 10)) out |= setbit(out, 7);
	if (bitset(in, 11)) out |= setbit(out, 47);
	if (bitset(in, 12)) out |= setbit(out, 15);
	if (bitset(in, 13)) out |= setbit(out, 55);
	if (bitset(in, 14)) out |= setbit(out, 23);
	if (bitset(in, 15)) out |= setbit(out, 63);
	if (bitset(in, 16)) out |= setbit(out, 31);
	if (bitset(in, 17)) out |= setbit(out, 38);
	if (bitset(in, 18)) out |= setbit(out, 6);
	if (bitset(in, 19)) out |= setbit(out, 46);
	if (bitset(in, 20)) out |= setbit(out, 14);
	if (bitset(in, 21)) out |= setbit(out, 54);
	if (bitset(in, 22)) out |= setbit(out, 22);
	if (bitset(in, 23)) out |= setbit(out, 62);
	if (bitset(in, 24)) out |= setbit(out, 30);
	if (bitset(in, 25)) out |= setbit(out, 37);
	if (bitset(in, 26)) out |= setbit(out, 5);
	if (bitset(in, 27)) out |= setbit(out, 45);
	if (bitset(in, 28)) out |= setbit(out, 13);
	if (bitset(in, 29)) out |= setbit(out, 53);
	if (bitset(in, 30)) out |= setbit(out, 21);
	if (bitset(in, 31)) out |= setbit(out, 61);
	if (bitset(in, 32)) out |= setbit(out, 29);
	if (bitset(in, 33)) out |= setbit(out, 36);
	if (bitset(in, 34)) out |= setbit(out, 4);
	if (bitset(in, 35)) out |= setbit(out, 44);
	if (bitset(in, 36)) out |= setbit(out, 12);
	if (bitset(in, 37)) out |= setbit(out, 52);
	if (bitset(in, 38)) out |= setbit(out, 20);
	if (bitset(in, 39)) out |= setbit(out, 60);
	if (bitset(in, 40)) out |= setbit(out, 28);
	if (bitset(in, 41)) out |= setbit(out, 35);
	if (bitset(in, 42)) out |= setbit(out, 3);
	if (bitset(in, 43)) out |= setbit(out, 43);
	if (bitset(in, 44)) out |= setbit(out, 11);
	if (bitset(in, 45)) out |= setbit(out, 51);
	if (bitset(in, 46)) out |= setbit(out, 19);
	if (bitset(in, 47)) out |= setbit(out, 59);
	if (bitset(in, 48)) out |= setbit(out, 27);
	if (bitset(in, 49)) out |= setbit(out, 34);
	if (bitset(in, 50)) out |= setbit(out, 2);
	if (bitset(in, 51)) out |= setbit(out, 42);
	if (bitset(in, 52)) out |= setbit(out, 10);
	if (bitset(in, 53)) out |= setbit(out, 50);
	if (bitset(in, 54)) out |= setbit(out, 18);
	if (bitset(in, 55)) out |= setbit(out, 58);
	if (bitset(in, 56)) out |= setbit(out, 26);
	if (bitset(in, 57)) out |= setbit(out, 33);
	if (bitset(in, 58)) out |= setbit(out, 1);
	if (bitset(in, 59)) out |= setbit(out, 41);
	if (bitset(in, 60)) out |= setbit(out, 9);
	if (bitset(in, 61)) out |= setbit(out, 49);
	if (bitset(in, 62)) out |= setbit(out, 17);
	if (bitset(in, 63)) out |= setbit(out, 57);
	if (bitset(in, 64)) out |= setbit(out, 25);
	
	return out;
}

ull pFinal(ull in)
{
	ull out = 0;

	if (bitset(in, 1)) out |= setbit(out, 58);
	if (bitset(in, 2)) out |= setbit(out, 50);
	if (bitset(in, 3)) out |= setbit(out, 42);
	if (bitset(in, 4)) out |= setbit(out, 34);
	if (bitset(in, 5)) out |= setbit(out, 26);
	if (bitset(in, 6)) out |= setbit(out, 18);
	if (bitset(in, 7)) out |= setbit(out, 10);
	if (bitset(in, 8)) out |= setbit(out, 2);
	if (bitset(in, 9)) out |= setbit(out, 60);
	if (bitset(in, 10)) out |= setbit(out, 52);
	if (bitset(in, 11)) out |= setbit(out, 44);
	if (bitset(in, 12)) out |= setbit(out, 36);
	if (bitset(in, 13)) out |= setbit(out, 28);
	if (bitset(in, 14)) out |= setbit(out, 20);
	if (bitset(in, 15)) out |= setbit(out, 12);
	if (bitset(in, 16)) out |= setbit(out, 4);
	if (bitset(in, 17)) out |= setbit(out, 62);
	if (bitset(in, 18)) out |= setbit(out, 54);
	if (bitset(in, 19)) out |= setbit(out, 46);
	if (bitset(in, 20)) out |= setbit(out, 38);
	if (bitset(in, 21)) out |= setbit(out, 30);
	if (bitset(in, 22)) out |= setbit(out, 22);
	if (bitset(in, 23)) out |= setbit(out, 14);
	if (bitset(in, 24)) out |= setbit(out, 6);
	if (bitset(in, 25)) out |= setbit(out, 64);
	if (bitset(in, 26)) out |= setbit(out, 56);
	if (bitset(in, 27)) out |= setbit(out, 48);
	if (bitset(in, 28)) out |= setbit(out, 40);
	if (bitset(in, 29)) out |= setbit(out, 32);
	if (bitset(in, 30)) out |= setbit(out, 24);
	if (bitset(in, 31)) out |= setbit(out, 16);
	if (bitset(in, 32)) out |= setbit(out, 8);
	if (bitset(in, 33)) out |= setbit(out, 57);
	if (bitset(in, 34)) out |= setbit(out, 49);
	if (bitset(in, 35)) out |= setbit(out, 41);
	if (bitset(in, 36)) out |= setbit(out, 33);
	if (bitset(in, 37)) out |= setbit(out, 25);
	if (bitset(in, 38)) out |= setbit(out, 17);
	if (bitset(in, 39)) out |= setbit(out, 9);
	if (bitset(in, 40)) out |= setbit(out, 1);
	if (bitset(in, 41)) out |= setbit(out, 59);
	if (bitset(in, 42)) out |= setbit(out, 51);
	if (bitset(in, 43)) out |= setbit(out, 43);
	if (bitset(in, 44)) out |= setbit(out, 35);
	if (bitset(in, 45)) out |= setbit(out, 27);
	if (bitset(in, 46)) out |= setbit(out, 19);
	if (bitset(in, 47)) out |= setbit(out, 11);
	if (bitset(in, 48)) out |= setbit(out, 3);
	if (bitset(in, 49)) out |= setbit(out, 61);
	if (bitset(in, 50)) out |= setbit(out, 53);
	if (bitset(in, 51)) out |= setbit(out, 45);
	if (bitset(in, 52)) out |= setbit(out, 37);
	if (bitset(in, 53)) out |= setbit(out, 29);
	if (bitset(in, 54)) out |= setbit(out, 21);
	if (bitset(in, 55)) out |= setbit(out, 13);
	if (bitset(in, 56)) out |= setbit(out, 5);
	if (bitset(in, 57)) out |= setbit(out, 63);
	if (bitset(in, 58)) out |= setbit(out, 55);
	if (bitset(in, 59)) out |= setbit(out, 47);
	if (bitset(in, 60)) out |= setbit(out, 39);
	if (bitset(in, 61)) out |= setbit(out, 31);
	if (bitset(in, 62)) out |= setbit(out, 23);
	if (bitset(in, 63)) out |= setbit(out, 15);
	if (bitset(in, 64)) out |= setbit(out, 7);

	return out;
}
#pragma endregion