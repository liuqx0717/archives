#include "stdafx.h"




namespace lqx {


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

}