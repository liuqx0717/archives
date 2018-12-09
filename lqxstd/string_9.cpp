#include "stdafx.h"
#include "string.h"

namespace lqx {

	char *StrFillStrA(char *dest, size_t deststrlen, char *str, size_t n)
	{
		size_t i, j, ii = 0;

		for (i = 0; i < n; ++i) {
			for (j = 0; str[j]; ++j, ++ii) {
				if (ii == deststrlen) return dest;
				dest[ii] = str[j];
			}
		}
		return dest;
	}


	char *CharFillStrLeftA(char *dest, const char *str, char ch, unsigned int width)
	{
		unsigned int len = strlen(str);
		if (width <= len) {
			strcpy(dest, str);
			return dest;
		}

		unsigned int i;

		for (i = 0; i < width - len; i++)
			dest[i] = ch;

		strcpy(dest + i, str);
		return dest;
	}


}