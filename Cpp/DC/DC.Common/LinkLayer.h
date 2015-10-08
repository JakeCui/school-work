#include "Common.h"

/*
Prepare frameBuffer, from the first charN bytes of charBuffer.
Adds the frame header, and adds parity bits to each char.
Returns the number of bytes placed in frameBuffer. */
uint l_prepareFrame(uch charBuffer[CHAR_LIMIT], uint charN, uch frameBuffer[CHAR_LIMIT + 3]);

/*
Prepare transmitBuffer, from the first frameN bytes of frameBuffer.
Splits each char into 0/1 chars, little-endian.
Returns the number of bytes placed in transmitBuffer. */
uint l_prepareTransmit(uch frameBuffer[CHAR_LIMIT + 3], uint frameN, uch transmitBuffer[(CHAR_LIMIT + 3) * 8]);

/*
Parse frameBuffer, from the first transmitN bytes of transmitBuffer.
Combines groups of 8 0/1 chars, little-endian, into chars.
Returns the number of bytes placed in frameBuffer. */
uint l_parseTransmit(uch transmitBuffer[(CHAR_LIMIT + 3) * 8], uint transmitN, uch frameBuffer[CHAR_LIMIT + 3]);

/*
Parse charBuffer, from the first frameN bytes of frameBuffer.
Strips parity, gets the data characters.
Returns the number of bytes places in charBuffer (as read from the frame header). */
uint l_parseFrame(uch frameBuffer[CHAR_LIMIT + 3], uint frameN, uch charBuffer[CHAR_LIMIT]);

/*
Validate the parity of the first frameN bytes of frameBuffer. */
bool l_validateFrame(uch frameBuffer[CHAR_LIMIT + 3], uint frameN);