#include "stdafx.h"

#include "network.h"

#pragma comment(lib,"Iphlpapi.lib") 

namespace lqx {


	void GetAdaptersInfo(void(*proc)(PIP_ADAPTER_INFO pIpAdapterInfo))
	{

		//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
		PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
		//�õ��ṹ���С,����GetAdaptersInfo����
		unsigned long stSize = sizeof(IP_ADAPTER_INFO);
		//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
		int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
		//��¼��������
		//��¼ÿ�������ϵ�IP��ַ����
		int IPnumPerNetCard = 0;
		if (ERROR_BUFFER_OVERFLOW == nRel)
		{
			//����������ص���ERROR_BUFFER_OVERFLOW
			//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
			//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
			//�ͷ�ԭ�����ڴ�ռ�
			delete pIpAdapterInfo;
			//���������ڴ�ռ������洢����������Ϣ
			pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
			//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
			nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
		}
		if (ERROR_SUCCESS == nRel)
		{
			//���������Ϣ
			//�����ж�����,���ͨ��ѭ��ȥ�ж�
			while (pIpAdapterInfo)
			{
				(*proc)(pIpAdapterInfo);
				pIpAdapterInfo = pIpAdapterInfo->Next;
			}

		}
		else
		{
			throw "GetAdaptersInfo����ʧ�ܡ�";
		}


		//�ͷ��ڴ�ռ�
		if (pIpAdapterInfo)
		{
			delete pIpAdapterInfo;
		}



		////PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
		//PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
		////�õ��ṹ���С,����GetAdaptersInfo����
		//unsigned long stSize = sizeof(IP_ADAPTER_INFO);
		////����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
		//int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
		////��¼��������
		//int netCardNum = 0;
		////��¼ÿ�������ϵ�IP��ַ����
		//int IPnumPerNetCard = 0;
		//if (ERROR_BUFFER_OVERFLOW == nRel)
		//{
		//	//����������ص���ERROR_BUFFER_OVERFLOW
		//	//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//	//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		//	//�ͷ�ԭ�����ڴ�ռ�
		//	delete pIpAdapterInfo;
		//	//���������ڴ�ռ������洢����������Ϣ
		//	pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//	//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		//	nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
		//}
		//if (ERROR_SUCCESS == nRel)
		//{
		//	//���������Ϣ
		//	//�����ж�����,���ͨ��ѭ��ȥ�ж�
		//	while (pIpAdapterInfo)
		//	{
		//		cout << "�������ƣ�" << pIpAdapterInfo->AdapterName << endl;
		//		cout << "����������" << pIpAdapterInfo->Description << endl;
		//		switch (pIpAdapterInfo->Type)
		//		{
		//		case MIB_IF_TYPE_OTHER:
		//			cout << "�������ͣ�" << "OTHER" << endl;
		//			break;
		//		case MIB_IF_TYPE_ETHERNET:
		//			cout << "�������ͣ�" << "ETHERNET" << endl;
		//			break;
		//		case MIB_IF_TYPE_TOKENRING:
		//			cout << "�������ͣ�" << "TOKENRING" << endl;
		//			break;
		//		case MIB_IF_TYPE_FDDI:
		//			cout << "�������ͣ�" << "FDDI" << endl;
		//			break;
		//		case MIB_IF_TYPE_PPP:
		//			printf("PP\n");
		//			cout << "�������ͣ�" << "PPP" << endl;
		//			break;
		//		case MIB_IF_TYPE_LOOPBACK:
		//			cout << "�������ͣ�" << "LOOPBACK" << endl;
		//			break;
		//		case MIB_IF_TYPE_SLIP:
		//			cout << "�������ͣ�" << "SLIP" << endl;
		//			break;
		//		default:

		//			break;
		//		}
		//		cout << "����MAC��ַ��";
		//		for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
		//			if (i < pIpAdapterInfo->AddressLength - 1)
		//			{
		//				printf("%02X-", pIpAdapterInfo->Address[i]);
		//			}
		//			else
		//			{
		//				printf("%02X\n", pIpAdapterInfo->Address[i]);
		//			}
		//		cout << "����IP��ַ���£�" << endl;
		//		//���������ж�IP,���ͨ��ѭ��ȥ�ж�
		//		IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
		//		do
		//		{
		//			cout << "IP ��ַ��" << pIpAddrString->IpAddress.String << endl;
		//			cout << "������ַ��" << pIpAddrString->IpMask.String << endl;
		//			cout << "���ص�ַ��" << pIpAdapterInfo->GatewayList.IpAddress.String << endl;
		//			pIpAddrString = pIpAddrString->Next;
		//		} while (pIpAddrString);
		//		pIpAdapterInfo = pIpAdapterInfo->Next;
		//		cout << "--------------------------------------------------------------------" << endl;
		//	}
		//}
		////�ͷ��ڴ�ռ�
		//if (pIpAdapterInfo)
		//{
		//	delete pIpAdapterInfo;
		//}
	}



}