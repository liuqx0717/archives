#include "stdafx.h"
#include "string.h"


namespace lqx {

	std::string BytesToHexString(const unsigned char *input, size_t length) {
		char HEXA[16] = {
			'0', '1', '2', '3',
			'4', '5', '6', '7',
			'8', '9', 'a', 'b',
			'c', 'd', 'e', 'f'
		};
		std::string str;
		str.reserve(length << 1);
		for (size_t i = 0; i < length; ++i) {
			int t = input[i];
			int a = t / 16;
			int b = t % 16;
			str.append(1, HEXA[a]);
			str.append(1, HEXA[b]);
		}
		return str;
	}

}