#include "stdafx.h"
#include "string.h"


namespace lqx {

	bool cmpa(const char *str1, const char *str2)
	{
		int i;
		for (i = 0; str1[i] && str2[i]; i++)
			if (str1[i] != str2[i] && str1[i] != str2[i] + ('A' - 'a') && str1[i] != str2[i] - ('A' - 'a')) return false;
		if (str1[i] || str2[i]) return false;
		return true;
	}

	char *trima(char *str, char *Charactors, _Trimtype Trimtype)
	{
		int start = 0, end;
		for (end = 0; str[end]; end++);
		int end_old = end -= 1;
		int i;
		char c;
		bool f;

		if (Trimtype&TRIM_LEFT) {
			for (; start <= end; start++) {
				f = true;
				for (int i = 0; c = Charactors[i]; i++) {
					if (str[start] == c) {
						f = false;
						break;
					}
				}
				if (f) break;
			}
		}
		if (Trimtype&TRIM_RIGHT) {
			for (; end >= start; end--) {
				f = true;
				for (int i = 0; c = Charactors[i]; i++) {
					if (str[end] == c) {
						f = false;
						break;
					}
				}
				if (f) break;
			}
		}
		if (start == 0 && end == end_old) return str;
		for (i = 0; i <= end - start; i++)
			str[i] = str[start + i];
		str[i] = '\0';

		return str;


	}

	char *fillstra(char *dest, size_t deststrlen, char *str, size_t n)
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



}