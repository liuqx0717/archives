#include "stdafx.h"
#include "string.h"


namespace lqx {

	size_t HexStringToBytesA(const char *input, unsigned char *output, size_t OutputBuffSize)
	{
		size_t n = 0;
		char tmp[3];
		char *endpos;
		tmp[2] = '\0';
		size_t i, j;
		for (i = 0, j = 0; input[i] && j < OutputBuffSize; ++i) {
			char c = input[i];
			if (c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f') {
				tmp[n] = c;
				n++;
				if (n == 2) {
					output[j] = (unsigned char)strtoul(tmp, &endpos, 16);
					j++;
					n = 0;
				}
			}
		}
		if (n != 0) throw "字符 0~9，a~f，A~F 出现的次数不是偶数。";
		return j;
	}


}