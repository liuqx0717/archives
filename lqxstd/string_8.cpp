#include "stdafx.h"




namespace lqx {


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
	)
	{
		if (Str[0] == '\0' || MaxSubstringCount == 0) return 0;

		//���ַ����ĸ���
		unsigned int n = 0;

		bool IsBetweenQuotationMarks = false;


		//��һ�����ַ���
		Results[n] = Str;
		n++;

		for (unsigned int i = 0; Str[i]; i++) {
			if (n == MaxSubstringCount) return n;

			if (!IsBetweenQuotationMarks && Str[i] == LeftQuotationMark) {      //�ж��Ƿ�Ϊ������
				IsBetweenQuotationMarks = true;
				continue;
			}
			if (IsBetweenQuotationMarks && Str[i] == RightQuotationMark) {     //�ж��Ƿ�Ϊ������
				IsBetweenQuotationMarks = false;
				continue;
			}

			if (!IsBetweenQuotationMarks) {         //�����ǰ�������������м�
				for (unsigned int j = 0; DelimChars[j]; j++) {
					if (Str[i] == DelimChars[j]) {        //�ҵ��ָ�����
						Str[i] = '\0';
						Results[n] = Str + i + 1;
						n++;

					}
				}
			}

		}

		//������ַ���
		if (IgnoreNullSubstring) {
			unsigned int i = 0;
			for (unsigned int j = 0; j < n; j++) {
				if (Results[j][0]) {           //���ַ�����Ϊ��
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