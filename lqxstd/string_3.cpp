#include "stdafx.h"
#include "string.h"

#include <vector>

//std::string *lqx::splitstr(const std::string &Str, unsigned int &substrc, char delims, char quotationmark)
//{
//	bool q = false;
//	unsigned int _i, _n, _l = Str.length();
//	char c;
//	std::string *ret;
//	std::vector<int> _pos;
//
//	_pos.reserve(200);
//
//	for (_i = 0; _i < _l; _i++){
//		c = Str[_i];
//		if (q) {
//			if (c == quotationmark) {
//				q = false;
//				continue;
//			}
//			continue;
//
//		}
//		if (c == quotationmark) {
//			q = true;
//			continue;
//		}
//		if (c == delims) _pos.push_back(_i);
//
//	}
//
//	_n = _pos.size() + 1;
//	ret = new std::string[_n];
//	if (_n == 1) ret[0].assign(Str);
//	else
//	{
//		ret[0].assign(Str, 0, _pos[0]);
//		for (_i = 1; _i < _n - 1; _i++) ret[_i].assign(Str, _pos[_i - 1] + 1, _pos[_i] - _pos[_i - 1] - 1);
//		ret[_i].assign(Str, _pos[_i - 1] + 1, _l - _pos[_i - 1] - 1);
//	}
//
//	substrc = _n;
//	return ret;
//
//}


bool issubstr(const char *source, size_t position, const char *substr)
{
	size_t i, j;
	for (i = position, j = 0; substr[j] && source[i]; ++j, ++i)
		if (source[i] != substr[j]) return false;
	if (substr[j]) return false;
	else return true;
}

std::string *lqx::splitstr(const std::string &Str, size_t *substrc, const char *delim, char quotationmark, bool ignore_null_substring)
{

	if (!delim[0]) {
		if (substrc) *substrc = 0;
		return 0;
	}


	size_t i, n = 0, l = Str.length(), ll, p = 0;
	for (ll = 0; delim[ll]; ++ll);
	bool q = false;
	char t;
	const char *source = Str.c_str();
	struct _pos {
		size_t begin;
		size_t n;
	};
	std::vector<_pos> pos;
	std::string *ret;

	pos.push_back({ 0, l });

	if (l >= ll) {
		for (i = 0; i <= l - ll; ++i){
			t = source[i];
			if (quotationmark) {
				if (q){
					if (t == quotationmark) {
						q = false;
						continue;
					}
					else continue;
				}
				else {
					if (t == quotationmark) {
						q = true;
						continue;
					}
				}
			}
			if (issubstr(source, i, delim)) {
				pos[p].n = i - pos[p].begin;
				i += ll;
				pos.push_back({ i, ll - i });
				i--;
				p++;
			}

			continue;
		}
	}
	ret = new std::string[p + 1];

	if (ignore_null_substring) {
		for (i = 0; i <= p; ++i) {
			if (pos[i].n) {
				ret[n] = Str.substr(pos[i].begin, pos[i].n);
				n++;
			}
		}
		if (substrc) *substrc = n;
		return ret;
	}
	else {
		for (i = 0; i <= p; ++i)
			ret[i] = Str.substr(pos[i].begin, pos[i].n);
		if (substrc) *substrc = i;
		return ret;
	}


}

