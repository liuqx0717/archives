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
	size_t HexStringToBytes(const char *input, unsigned char *output, size_t OutputBuffSize);   //���� 0~9��a~f��A~F ������ַ�������ת�����ֽ�����0~9��a~f��A~F �������ż���Ρ�

	char *trima(__inout char *str, char *Charactors = " \t", _Trimtype Trimtype = TRIM_BOTH);
	wchar_t *trimw(__inout wchar_t *str, wchar_t *Charactors = L" \t", _Trimtype Trimtype = TRIM_BOTH);


	//��ָ���ַ����ظ���䵽��һ���ַ���
	char *StrFillStrA(__inout char *dest, __in size_t deststrlen, __in char *str, __in size_t n);

	char *CharFillStrLeftA(char *dest, const char *str, char ch, unsigned int width);
	

	bool cmpw(const wchar_t *str1, const wchar_t *str2); //�����ִ�Сд����ͬ�򷵻�true
	bool cmpa(const char *str1, const char *str2); //�����ִ�Сд����ͬ�򷵻�true

	size_t HexStringToBytesA(const char *input, unsigned char *output, size_t OutputBuffSize);  //����ֵΪд��output���ֽ�����
	size_t HexStringToBytesW(const wchar_t *input, unsigned char *output, size_t OutputBuffSize);

	size_t BytesToHexStringW(const unsigned char *input, size_t inputlen, wchar_t *output, size_t outputlen);//outputĩβ�Զ���0,����ֵΪ�ַ�����(������0)

	std::string *splitstr(__in const std::string &Str, __out_opt size_t *substrc, __in const char *delims, __in_opt char quotationmark = '\"', bool ignore_null_substring = false);




	//���ٷָ��ַ����������ֵ����ַ��ָ��ʹ�öѿռ䡣
	//��ı�Str�����ݣ���Str�еķָ����滻Ϊ'\0'��
	//DelimChars Ϊ�ָ���ַ�������"\n\t"������ʶ�����ַָ��������к�����
	//Results��һ�����飬������ַ�����ָ�롣
	//MaxSubstringCount Ϊ ������ַ����������� Results ����Ĵ�С����
	//�����ַ�����������MaxSubstringCount���Ὣ�����Ĳ��ֺϲ�Ϊ���һ�����ַ�����
	//IgnoreNullSubstringָ���Ƿ����Result�����еĿ��ַ�����
	//LeftQuotationMarkΪ�����ţ�RightQuotationMarkΪ�����š��������ʶ�����ţ���������Ϊ'\0'���ɡ�
	//����ֵΪ���ַ���������
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