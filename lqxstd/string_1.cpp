#include "stdafx.h"
#include "string.h"


namespace lqx {

	std::string &trim(std::string &Str, char *Charactors, _Trimtype Trimtype)
	{
		int start = 0, end;
		const char *str = Str.c_str();
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
		if (start == 0 && end == end_old) return Str;

		Str.assign(str + start, end - start + 1);

		return Str;

	}

	std::string &erasechr(std::string &Str, char ChL, char ChH)
	{
		bool f = false;
		size_t _l = Str.length(), i, j;
		char c;
		char *tmp = new char[_l + 2];
		for (i = 0, j = 0; i < _l; ++i) {
			c = Str[i];
			if (c < ChL || c > ChH) {
				tmp[j] = c;
				j++;
			}
			else
				f = true;
		}
		if (_l == j) goto r;
		tmp[j] = '\0';
		if (f) Str.assign(tmp);
	r:
		delete[] tmp;
		return Str;
	}

	std::string &lqx::fill_left(std::string &Str, size_t width, char Ch)
	{
		size_t _len = Str.length();
		if (width <= _len) return Str;
		std::string tmp;
		tmp.reserve(width);
		tmp.assign(Str);
		Str.assign(width - _len, Ch);
		Str.append(tmp);
		return Str;

	}

	std::string &lqx::fill_right(std::string &Str, size_t width, char Ch)
	{
		size_t _len = Str.length();
		if (width <= _len) return Str;
		Str.append(width - _len, Ch);
		return Str;
	}



}