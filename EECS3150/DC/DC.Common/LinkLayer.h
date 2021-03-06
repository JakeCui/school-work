#include "Common.h"

/*
Add the ASCII parity bit of the first charN bytes of charBuffer. */
void l_addCharParity(uch charBuffer[CHAR_LIMIT], uint charN);

/*
Validate the ASCII parity of the first charN bytes of charBuffer. 
Sets flag FLAG_ER_PARITY in charBufferFlags on each bad character.
Returns true if all valid, false otherwise. */
bool l_validateCharParity(uch charBuffer[CHAR_LIMIT], uint charN, uch charBufferFlags[CHAR_LIMIT]);

/*
Remove the ASCII parity bit of the first charN bytes of charBuffer. */
void l_stripCharParity(uch charBuffer[CHAR_LIMIT], uint charN);

/*
Prepare the frame header.
Adds two SYN (0x22) characters and the data length. */
void l_prepareFrameHeader(uch transmitBuffer[TRANSMIT_LIMIT], uint charN);

/*
Prepare dataBuffer, for no error detection or correction.
Builds from the first charN bytes of charBuffer.
Returns the number of bytes placed in dataBuffer. */
uint l_prepareData(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT]);

/*
Parse charBuffer, for no error detection or correction.
Builds from the first dataN bytes of dataBuffer.
Returns the number of bytes placed in charBuffer. */
uint l_parseData(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT]);

/*
Prepare dataBuffer, for CRC-ANSI error detection.
Builds from the first charN bytes of charBuffer.
Returns the number of bytes placed in dataBuffer. */
uint l_prepareDataCrc(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT]);

/*
Validate the CRC-ANSI of the first dataN bytes of dataBuffer (including the CRC checksum).
Returns true if valid, false otherwise. */
bool l_validateDataCrc(uch dataBuffer[DATA_LIMIT], uint dataN);

/*
Parse charBuffer, for CRC-ANSI error detection. The CRC is assumed to be valid.
Builds from the first dataN bytes of dataBuffer.
Returns the number of bytes placed in charBuffer. */
uint l_parseDataCrc(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT]);

/*
Prepare dataBuffer, for Hamming 12-8 error correction.
Builds from the first charN bytes of charBuffer.
Returns the number of bytes placed in dataBuffer. */
uint l_prepareDataHamming(uch charBuffer[CHAR_LIMIT], uint charN, uch dataBuffer[DATA_LIMIT]);

/*
Validate the Hamming 12-8 code on the first dataN bits of dataBuffer.
If a character is identified bad, flag FLAG_ER_HAMMING_DETECTED is set in charBufferFlags.
If a character is corrected, flag FLAG_ER_HAMMING_CORRECTED is set in charBufferFlags.
Returns true if all valid (no detections or corrections), false otherwise. */
bool l_validateDataHamming(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBufferFlags[CHAR_LIMIT]);

/*
Parse charBuffer, for Hamming 12-8 error correction.
Builds from the first dataN bytes of dataBuffer.
Returns the number of bytes placed in charBuffer. */
uint l_parseDataHamming(uch dataBuffer[DATA_LIMIT], uint dataN, uch charBuffer[CHAR_LIMIT]);

/*
Randomly flip bits in the first dataN bits of dataBuffer.
Each bit has a 5% chance of being flipped, up to maxErrors across all the bits.
Each bit position flipped is added to the errorPos array.
Returns the number of bits flipped (also the number of values placed in errorPos). */
int l_introduceErrors(uch dataBuffer[DATA_LIMIT], uint dataN, int maxErrors, int errorPos[]);

/*
Encode the first dataN bytes of dataBuffer using HDB3. */
void l_encodeHdb3(uch dataBuffer[DATA_LIMIT], uint dataN);

/*
Decode the first dataN bytes of dataBuffer using HDB3. */
void l_decodeHdb3(uch dataBuffer[DATA_LIMIT], uint dataN);