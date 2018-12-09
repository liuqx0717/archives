#include "stdafx.h"

#ifndef _LQXSTD_STRING_
#define _LQXSTD_STRING_

#include <string>


namespace lqx {

	enum _Trimtype{
		TRIM_LEFT = 0x1,
		TRIM_RIGHT = 0x2,
		TRIM_BOTH = 0x3
	};
	std::string &trim(__inout std::string &Str_, __in char *Charactors = " \t", __in _Trimtype Trimtype = TRIM_BOTH);
	inline std::string &trim_left(__inout std::string &Str, __in char *Charactors = " \t") { trim(Str, Charactors, TRIM_LEFT); }
	inline std::string &trim_right(__inout std::string &Str, __in char *Charactors = " \t") { trim(Str, Charactors , TRIM_RIGHT); }
	std::string &erasechr(__inout std::string &Str, char ChL, char ChH);


	std::string &fill_left(__inout std::string &Str, __in size_t width, __in char Ch = ' ');
	std::string &fill_right(__inout std::string &Str, __in size_t width, __in char Ch = ' ');

	std::string BytesToHexString(__in const unsigned char *input, __in size_t length);
	size_t HexStringToBytes(const char *input, unsigned char *output, size_t OutputBuffSize);   //忽略 0~9，a~f，A~F 以外的字符，返回转换的字节数。0~9，a~f，A~F 必须出现偶数次。

	char *trima(__inout char *str, char *Charactors = " \t", _Trimtype Trimtype = TRIM_BOTH);
	wchar_t *trimw(__inout wchar_t *str, wchar_t *Charactors = L" \t", _Trimtype Trimtype = TRIM_BOTH);


	//已指定字符串重复填充到另一个字符串
	char *StrFillStrA(__inout char *dest, __in size_t deststrlen, __in char *str, __in size_t n);

	char *CharFillStrLeftA(char *dest, const char *str, char ch, unsigned int width);
	

	bool cmpw(const wchar_t *str1, const wchar_t *str2); //不区分大小写，相同则返回true
	bool cmpa(const char *str1, const char *str2); //不区分大小写，相同则返回true

	size_t HexStringToBytesA(const char *input, unsigned char *output, size_t OutputBuffSize);  //返回值为写入output的字节数。
	size_t HexStringToBytesW(const wchar_t *input, unsigned char *output, size_t OutputBuffSize);

	size_t BytesToHexStringW(const unsigned char *input, size_t inputlen, wchar_t *output, size_t outputlen);//output末尾自动补0,返回值为字符个数(不包括0)

	std::string *splitstr(__in const std::string &Str, __out_opt size_t *substrc, __in const char *delims, __in_opt char quotationmark = '\"', bool ignore_null_substring = false);




	//快速分割字符串，按多种单个字符分割。不使用堆空间。
	//会改变Str的内容：将Str中的分隔符替换为'\0'。
	//DelimChars 为分割的字符，例如"\n\t"，代表识别两种分隔符：换行和跳格。
	//Results是一个数组，存放子字符串的指针。
	//MaxSubstringCount 为 最大子字符串个数（即 Results 数组的大小）。
	//若子字符串个数超过MaxSubstringCount，会将超出的部分合并为最后一个子字符串。
	//IgnoreNullSubstring指定是否清除Result数组中的空字符串。
	//LeftQuotationMark为左引号，RightQuotationMark为右引号。如果无需识别引号，则将其设置为'\0'即可。
	//返回值为子字符串个数。
	unsigned int splitstr(
		char *Str,
		const char *DelimChars,
		char* Results[],
		unsigned int MaxSubstringCount,
		bool IgnoreNullSubstring,
		char LeftQuotationMark,
		char RightQuotationMark
	);




}











#endif //_LQXSTD_STRING_