#ifndef __STRINGALG_H
#define __STRINGALG_H


#include "Message.h"

enum StringAlg_TrimType {
	StringAlg_TRIM_LEFT = 0x1,
	StringAlg_TRIM_RIGHT = 0x2,
	StringAlg_TRIM_BOTH = 0x3
};


//快速比较不区分大小写的字符串，ascii编码
bool StringAlg_CmpA(const char *str1, const char *str2);



//去除首尾指定的字符，同时除去多种字符。ascii编码。
//会改变Str的内容，返回值为Str
//Charactors为要除去的字符，例如："\r\n\t "，代表除去回车符、换行符、跳格、空格。
char *StringAlg_TrimA(char *str, char *Charactors, StringAlg_TrimType Trimtype);



//快速分割字符串，按多种单个字符分割。不使用堆空间。
//会改变Str的内容：将Str中的分隔符替换为'\0'。
//DelimChars 为分割的字符，例如"\n\t"，代表识别两种分隔符：换行和跳格。
//Results是一个数组，存放子字符串的指针。
//MaxSubstringCount 为 最大子字符串个数（即 Results 数组的大小）。
//若子字符串个数超过MaxSubstringCount，会将超出的部分合并为最后一个子字符串。
//IgnoreNullSubstring指定是否清除Result数组中的空字符串。
//LeftQuotationMark为左引号，RightQuotationMark为右引号。如果无需识别引号，则将其设置为'\0'即可。
//返回值为子字符串个数。
unsigned int StringAlg_Split(
	char *Str,
	const char *DelimChars,
	char* Results[],
	unsigned int MaxSubstringCount,
	bool IgnoreNullSubstring,
	char LeftQuotationMark,
	char RightQuotationMark
);



char *StringAlg_CharFillStrLeftA(char *dest, const char *str, char ch, unsigned int width);


//Precision表示为小数位数。例如要保留4位小数，则Precision应为4
//简单地分离小数部分和整数部分。如果指数部分过大，则不能正常转换。
void StringAlg_ftoa(float f, char *dest, unsigned int Precision);


#endif // !__STRINGALG_H
