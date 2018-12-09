#include "stdafx.h"
#include "string.h"


namespace lqx {

	size_t BytesToHexStringW(const unsigned char *input, size_t inputlen, wchar_t *output, size_t outputlen) {
		wchar_t HEXW[16] = {
			'0', '1', '2', '3',
			'4', '5', '6', '7',
			'8', '9', 'A', 'B',
			'C', 'D', 'E', 'F'
		};
		size_t n = 0;
		if (outputlen < 3) return 0;
		for (size_t i = 0; i < inputlen && n < outputlen - 2; ++i) {
			int t = input[i];
			int a = t / 16;
			int b = t % 16;
			output[n++] = HEXW[a];
			output[n++] = HEXW[b];
		}
		output[n] = 0;
		return n;
	}

	size_t HexStringToBytesW(const wchar_t *input, unsigned char *output, size_t OutputBuffSize)
	{
		size_t n = 0;
		wchar_t tmp[3];
		wchar_t *endpos;
		tmp[2] = 0;
		size_t i, j;
		for (i = 0, j = 0; input[i] && j < OutputBuffSize; ++i) {
			wchar_t c = input[i];
			if (c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f') {
				tmp[n] = c;
				n++;
				if (n == 2) {
					output[j] = (unsigned char)wcstoul(tmp, &endpos, 16);
					j++;
					n = 0;
				}
			}
		}
		if (n != 0) throw "字符 0~9，a~f，A~F 出现的次数不是偶数。";
		return j;
	}


}