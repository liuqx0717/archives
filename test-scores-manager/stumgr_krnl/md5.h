#include "stdafx.h"

#ifndef MD5_H
#define MD5_H

#include <string>
//#include <fstream>

/* Type define */
typedef unsigned char byte;
typedef unsigned long ulong;


/* MD5 declaration. */
class MD5 {
public:
	MD5() { reset(); }
	MD5(const void *input, size_t length) { reset(); update(input, length); }
	MD5(const std::string &str) { reset(); update(str); }
	//MD5(std::ifstream &in){ reset(); update(in); }
	void update(const void *input, size_t length) { update((const byte*)input, length); }
	void update(const std::string &str) { update((const byte*)str.c_str(), str.length()); }
	//void update(std::ifstream &in);
	const byte* digest();
	std::string toString() { return bytesToHexString(digest(), 16); }
	void reset() {
		_finished = false;
		/* reset number of bits. */
		_count[0] = _count[1] = 0;
		/* Load magic initialization constants. */
		_state[0] = 0x67452301;
		_state[1] = 0xefcdab89;
		_state[2] = 0x98badcfe;
		_state[3] = 0x10325476;
	}
private:
	void update(const byte *input, size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const ulong *input, byte *output, size_t length);
	void decode(const byte *input, ulong *output, size_t length);
	std::string bytesToHexString(const byte *input, size_t length);

	/* class uncopyable */
	MD5(const MD5&);
	MD5& operator=(const MD5&);
private:
	ulong _state[4];	/* state (ABCD) */
	ulong _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];	/* input buffer */
	byte _digest[16];	/* message digest */
	bool _finished;		/* calculate finished ? */

	static const byte PADDING[64];	/* padding for calculate */
	static const char HEX[16];
	static const size_t BUFFER_SIZE = 1024;
};
	

#endif/*MD5_H*/