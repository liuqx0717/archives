#include "stdafx.h"
#include "string.h"


namespace lqx {

	bool cmpw(const wchar_t *str1, const wchar_t *str2)
	{
		int i;
		for (i = 0; str1[i] && str2[i]; i++)
			if (str1[i] != str2[i] && str1[i] != str2[i] + ('A' - 'a') && str1[i] != str2[i] - ('A' - 'a')) return false;
		if (str1[i] || str2[i]) return false;
		return true;
	}

	wchar_t *trimw(wchar_t *str, wchar_t *Charactors, _Trimtype Trimtype)
	{
		int start = 0, end;
		for (end = 0; str[end]; end++);
		int end_old = end -= 1;
		int i;
		wchar_t c;
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



}