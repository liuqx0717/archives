#include "StringAlg.h"

#include "string.h"

#include <stdlib.h>


float abs(float f)
{
	if (f > 0) return f;
	else return -f;
}


//快速比较不区分大小写的字符串，ascii编码
bool StringAlg_CmpA(const char *str1, const char *str2)    
{
	int i;
	for (i = 0; str1[i] && str2[i]; i++)
		if (str1[i] != str2[i] && str1[i] != str2[i] + ('A' - 'a') && str1[i] != str2[i] - ('A' - 'a')) return false;
	if (str1[i] || str2[i]) return false;
	return true;
}



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
)
{
	if (Str[0] == '\0' || MaxSubstringCount == 0) return 0;

	//子字符串的个数
	unsigned int n = 0;

	bool IsBetweenQuotationMarks = false;


	//第一个子字符串
	Results[n] = Str;
	n++;

	for (unsigned int i = 0; Str[i]; i++) {
		if (n == MaxSubstringCount) return n;

		if (!IsBetweenQuotationMarks && Str[i] == LeftQuotationMark) {      //判断是否为左引号
			IsBetweenQuotationMarks = true;
			continue;
		}
		if (IsBetweenQuotationMarks && Str[i] == RightQuotationMark) {     //判断是否为右引号
			IsBetweenQuotationMarks = false;
			continue;
		}

		if (!IsBetweenQuotationMarks) {         //如果当前不在两个引号中间
			for (unsigned int j = 0; DelimChars[j]; j++) {
				if (Str[i] == DelimChars[j]) {        //找到分隔符了
					Str[i] = '\0';
					Results[n] = Str + i + 1;
					n++;

				}
			}
		}

	}

	//清除空字符串
	if (IgnoreNullSubstring) {
		unsigned int i = 0;
		for (unsigned int j = 0; j < n; j++) {
			if (Results[j][0]) {           //子字符串不为空
				Results[i] = Results[j];
				i++;
			}
		}
		return i;
	}
	else {
		return n;
	}

}



//去除首尾指定的字符，同时除去多种字符。ascii编码。
//会改变Str的内容，返回值为Str
//Charactors为要除去的字符，例如："\r\n\t "，代表除去回车符、换行符、跳格、空格。
char *StringAlg_TrimA(char *str, char *Charactors, StringAlg_TrimType Trimtype)
{
	int start = 0, end;
	for (end = 0; str[end]; end++);
	int end_old = end -= 1;
	int i;
	char c;
	bool f;

	if (Trimtype&StringAlg_TRIM_LEFT) {
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
	if (Trimtype&StringAlg_TRIM_RIGHT) {
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


char *StringAlg_CharFillStrLeftA(char *dest, const char *str, char ch, unsigned int width)
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




//Precision表示为小数位数。例如要保留4位小数，则Precision应为4
//简单地分离小数部分和整数部分。如果指数部分过大，则不能正常转换。
void StringAlg_ftoa(float f, char *dest, unsigned int Precision)
{
	int intpart = (int)f;
	char tmp[64];
	if (f > -1 && f < 0) {
		strcpy(dest, "-0");
	}
	else {
		itoa(intpart, dest, 10);
	}
	unsigned int len = strlen(dest);
	dest[len] = '.';
	len++;

	unsigned int Multiply = 1;
	for (int i = 0; i < Precision; i++) {
		Multiply *= 10;
	}

	itoa((int)(abs(f - intpart) * (float)Multiply), tmp, 10);
	StringAlg_CharFillStrLeftA(dest + len, tmp, '0', Precision);

}


