#include "stdafx.h"

#include "network.h"

#pragma comment(lib, "wlanapi.lib")

namespace lqx {

	BOOL _network_1_Enabled = FALSE;

	void QueryHostedNetwork(_HostedNetworkInfo *HostedNetworkInfo)
	{

		HANDLE ClientHandle;
		DWORD NegotiatedVersion;

		//��ó�������ľ��
		if (WlanOpenHandle(2, NULL, &NegotiatedVersion, &ClientHandle) != ERROR_SUCCESS)
			throw "WlanOpenHandle����ʧ�ܡ�";
		//�����δ�Գ�������������ã������Զ����ó������硣����Ѿ����ù�������������SSID������֮��ģ�������ԭ�����á�
		if (WlanHostedNetworkInitSettings(ClientHandle, NULL, NULL) != ERROR_SUCCESS)
			throw "WlanHostedNetworkInitSettings����ʧ�ܡ�";
		

		//��ȡ����״̬
		PWLAN_HOSTED_NETWORK_STATUS pHostedNetworkStatus = NULL;
		if (WlanHostedNetworkQueryStatus(ClientHandle, &pHostedNetworkStatus, NULL) != ERROR_SUCCESS)
			throw("WlanHostedNetworkQueryStatus����ʧ�ܡ�");
		if (pHostedNetworkStatus->HostedNetworkState != wlan_hosted_network_active)  //�Ƿ���������
			HostedNetworkInfo->Active = false;
		else
			HostedNetworkInfo->Active = true;
		HostedNetworkInfo->NumberOfPeers = pHostedNetworkStatus->dwNumberOfPeers;    //��ǰ������
		WlanFreeMemory(pHostedNetworkStatus);


		//�鿴�Ƿ������ó������磨��netsh wlan set hostednetwork mode=allow/disallow���õ����ݣ�
		DWORD ReturnValue;
		DWORD DataSize;
		PBOOL pEnabled = NULL;
		WLAN_OPCODE_VALUE_TYPE WlanOpcodeValueType;
		ReturnValue = WlanHostedNetworkQueryProperty(
			ClientHandle,
			wlan_hosted_network_opcode_enable,
			&DataSize,
			(PVOID*)&pEnabled,
			&WlanOpcodeValueType,
			NULL
		);
		if (ReturnValue != ERROR_SUCCESS) throw "WlanHostedNetworkQueryProperty����ʧ�ܡ�";
		_network_1_Enabled = *pEnabled;
		WlanFreeMemory(pEnabled);


		//��ȡ��ǰ����������������
		ULONG SSIDLengthInBytes;
		UCHAR *SSID_;
		PWLAN_HOSTED_NETWORK_CONNECTION_SETTINGS pHostedNetworkConnectionSettings = NULL;
		ReturnValue = WlanHostedNetworkQueryProperty(
			ClientHandle,
			wlan_hosted_network_opcode_connection_settings,
			&DataSize,
			(PVOID*)&pHostedNetworkConnectionSettings,
			&WlanOpcodeValueType,
			NULL
		);

		if (ReturnValue != ERROR_SUCCESS) throw "WlanHostedNetworkQueryProperty����ʧ�ܡ�";
		SSIDLengthInBytes = pHostedNetworkConnectionSettings->hostedNetworkSSID.uSSIDLength;  //SSID���ȣ�������\0��
		SSID_ = pHostedNetworkConnectionSettings->hostedNetworkSSID.ucSSID;                   //SSID�ַ���
		strcpy_s(HostedNetworkInfo->SSID, 32, (char*)SSID_);
		HostedNetworkInfo->MaxNumberOfPeers = pHostedNetworkConnectionSettings->dwMaxNumberOfPeers; //���������
		WlanFreeMemory(pHostedNetworkConnectionSettings);


		//��õ�ǰ���õ�����
		DWORD KeyLength;
		PUCHAR KeyData;
		BOOL IsPassPhrase;
		BOOL Persistent;
		WLAN_HOSTED_NETWORK_REASON FailReason;
		ReturnValue = WlanHostedNetworkQuerySecondaryKey(
			ClientHandle,
			&KeyLength,
			&KeyData,
			&IsPassPhrase,
			&Persistent,
			&FailReason,
			NULL
		);
		if (ReturnValue != ERROR_SUCCESS) throw "WlanHostedNetworkQuerySecondaryKey����ʧ�ܡ�";
		if (IsPassPhrase) {
			HostedNetworkInfo->IsPassPhase = true;
			strcpy_s(HostedNetworkInfo->Key, 64, (char*)KeyData);
		}
		else {
			HostedNetworkInfo->IsPassPhase = false;
			memcpy_s(HostedNetworkInfo->Key, 64, KeyData, 32);
		}
		WlanFreeMemory(KeyData);


		//��ȡ��֤��ʽ�������㷨
		PWLAN_HOSTED_NETWORK_SECURITY_SETTINGS pHostedNetworkSecuritySettings = NULL;
		ReturnValue = WlanHostedNetworkQueryProperty(
			ClientHandle,
			wlan_hosted_network_opcode_security_settings,
			&DataSize,
			(PVOID*)&pHostedNetworkSecuritySettings,
			&WlanOpcodeValueType,
			NULL
		);
		HostedNetworkInfo->dot11AuthAlgo = pHostedNetworkSecuritySettings->dot11AuthAlgo;
		HostedNetworkInfo->dot11CipherAlgo = pHostedNetworkSecuritySettings->dot11CipherAlgo;
		WlanFreeMemory(pHostedNetworkSecuritySettings);


		WlanCloseHandle(ClientHandle, NULL);

	}



	void SetHostedNetwork(_HostedNetworkInfo *HostedNetworkInfo)
	{

		HANDLE ClientHandle;
		DWORD NegotiatedVersion;

		if (WlanOpenHandle(2, NULL, &NegotiatedVersion, &ClientHandle) != ERROR_SUCCESS)
			throw "WlanOpenHandle����ʧ�ܡ�";

		//���ó������磨SSID�Լ������������
		DWORD ReturnValue;
		WLAN_HOSTED_NETWORK_REASON FailReason;
		WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS HostedNetworkConnectionSettings;
		DOT11_SSID Dot11SSID;
		strcpy_s((char*)Dot11SSID.ucSSID, 32, (char*)(HostedNetworkInfo->SSID));
		Dot11SSID.uSSIDLength = strlen((char*)(HostedNetworkInfo->SSID));
		HostedNetworkConnectionSettings.dwMaxNumberOfPeers = HostedNetworkInfo->MaxNumberOfPeers;
		HostedNetworkConnectionSettings.hostedNetworkSSID = Dot11SSID;
		ReturnValue = WlanHostedNetworkSetProperty(
			ClientHandle,
			wlan_hosted_network_opcode_connection_settings,
			sizeof(HostedNetworkConnectionSettings),
			(PVOID)&HostedNetworkConnectionSettings,
			&FailReason,
			NULL
		);
		if (ReturnValue != ERROR_SUCCESS) throw "WlanHostedNetworkSetProperty����ʧ�ܡ�";


		//��������
		if (HostedNetworkInfo->IsPassPhase) {     //����Ϊ�ַ���
			ReturnValue = WlanHostedNetworkSetSecondaryKey(
				ClientHandle,
				strlen((char*)(HostedNetworkInfo->Key)) + 1,   //(����ĳ��ȹ涨��'\0'������)
				(PUCHAR)(HostedNetworkInfo->Key),
				TRUE,
				TRUE,
				&FailReason,
				NULL
			);
		}
		else {                                    //����Ϊ32�ֽڵĶ���������
			ReturnValue = WlanHostedNetworkSetSecondaryKey(
				ClientHandle,
				32,
				(PUCHAR)(HostedNetworkInfo->Key),
				FALSE,
				TRUE,
				&FailReason,
				NULL
			);
		}
		if (ReturnValue != ERROR_SUCCESS) throw "WlanHostedNetworkSetSecondaryKey����ʧ�ܡ�";

		WlanCloseHandle(ClientHandle, NULL);
	}



	void StartHostedNetwork()
	{
		HANDLE ClientHandle;
		DWORD NegotiatedVersion;

		if (WlanOpenHandle(2, NULL, &NegotiatedVersion, &ClientHandle) != ERROR_SUCCESS)
			throw "WlanOpenHandle����ʧ�ܡ�";

		DWORD ReturnValue;
		BOOL Enabled = TRUE;
		WLAN_HOSTED_NETWORK_REASON FailReason;

		//����������类���ã���netsh wlan set hostednetwork mode=disallow�����ã������Ƚ������״̬��
		if (!_network_1_Enabled) {
			ReturnValue = WlanHostedNetworkSetProperty(
				ClientHandle,
				wlan_hosted_network_opcode_enable,
				sizeof(Enabled),
				(PVOID)&Enabled,
				&FailReason,
				NULL
			);
			if (ReturnValue != ERROR_SUCCESS) throw "WlanHostedNetworkSetProperty���ó�������ʧ�ܡ�";
		}


		//���ó������硣ʹ��WlanHostedNetworkForceStart����ʹ�������˳������������Ի�������С�
		if (WlanHostedNetworkForceStart(ClientHandle, &FailReason, NULL) != ERROR_SUCCESS)
			throw "WlanHostedNetworkForceStart����ʧ�ܡ�";

		WlanCloseHandle(ClientHandle, NULL);
	}


	void StopHostedNetwork()
	{
		HANDLE ClientHandle;
		DWORD NegotiatedVersion;

		if (WlanOpenHandle(2, NULL, &NegotiatedVersion, &ClientHandle) != ERROR_SUCCESS)
			throw "WlanOpenHandle����ʧ�ܡ�";

		WLAN_HOSTED_NETWORK_REASON FailReason;
		if (WlanHostedNetworkForceStop(ClientHandle, &FailReason, NULL) != ERROR_SUCCESS)
			throw "WlanHostedNetworkForceStop����ʧ�ܡ�";

		WlanCloseHandle(ClientHandle, NULL);
	}



	void DisableHostedNetwork()
	{
		HANDLE ClientHandle;
		DWORD NegotiatedVersion;

		if (WlanOpenHandle(2, NULL, &NegotiatedVersion, &ClientHandle) != ERROR_SUCCESS)
			throw "WlanOpenHandle����ʧ�ܡ�";

		DWORD ReturnValue;
		BOOL Enabled = FALSE;
		WLAN_HOSTED_NETWORK_REASON FailReason;

		ReturnValue = WlanHostedNetworkSetProperty(
			ClientHandle,
			wlan_hosted_network_opcode_enable,
			sizeof(Enabled),
			(PVOID)&Enabled,
			&FailReason,
			NULL
		);
		if (ReturnValue != ERROR_SUCCESS) throw "WlanHostedNetworkSetProperty���ó�������ʧ�ܡ�";

		WlanCloseHandle(ClientHandle, NULL);

	}



	void EnumConnections(void(*Proc)(_NetConnectionInfo *NetConnectionInfo, _SharingType *SharingType, _ConnectingAction *ConnectingAction))
	{
		CoInitialize(NULL);
		CoInitializeSecurity(
			NULL,
			-1,
			NULL,
			NULL,
			RPC_C_AUTHN_LEVEL_PKT,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE,
			NULL
		);

		INetSharingManager * pNSM = NULL;
		HRESULT hr = ::CoCreateInstance(
			__uuidof(NetSharingManager),
			NULL, CLSCTX_ALL,
			__uuidof(INetSharingManager),
			(void**)&pNSM
		);
		if (!pNSM) throw L"NetSharingManager��ȡʧ�ܡ�";

		INetConnection * pNC = NULL;
		INetSharingEveryConnectionCollection * pNSECC = NULL;


		// ö���豸(���������ӣ������������ӡ�����)  
		hr = pNSM->get_EnumEveryConnection(&pNSECC);
		if (!pNSECC) {
			//pNSM->Release();
			throw L"get_EnumEveryConnectionʧ�ܡ�";
		}


		IEnumVARIANT * pEV = NULL;
		IUnknown * pUnk = NULL;
		hr = pNSECC->get__NewEnum(&pUnk);
		if (pUnk)
		{
			hr = pUnk->QueryInterface(__uuidof(IEnumVARIANT), (void**)&pEV);
			if (!pEV) {
				//pNSM->Release();
				//pNSECC->Release();
				//pUnk->Release();
				throw L"QueryInterfaceʧ�ܡ�";
			}
		}
		else {
			//pNSM->Release();
			//pNSECC->Release();
			throw L"get__NewEnumʧ�ܡ�";
		}


		if (pEV)
		{
			VARIANT v;
			VariantInit(&v);// ��ʼ�� ���� ����VARIANT���Ǵ���ɲ�׽��  
			BOOL bFoundIt = FALSE;
			INetSharingConfiguration * pNSC = NULL;
			while (S_OK == pEV->Next(1, &v, NULL))// ö�������е�Ԫ�� �����ش���ֵ  
			{
				if (V_VT(&v) == VT_UNKNOWN)// ����λ������  
				{
					V_UNKNOWN(&v)->QueryInterface(__uuidof(INetConnection), (void**)&pNC);  // ��ѯ�豸�Ƿ�֧�ֽӿ�  
					if (pNC)
					{
						NETCON_PROPERTIES* pNP = NULL;
						_NetConnectionInfo NetConnectionInfo;
						_SharingType SharingType, SharingType_old;
						_ConnectingAction ConnectingAction = ConnectingAction_None;

						pNC->GetProperties(&pNP);// ��ȡ�豸����  
						NetConnectionInfo.DeviceName = pNP->pszwDeviceName;
						NetConnectionInfo.Name = pNP->pszwName;
						NetConnectionInfo.Status = pNP->Status;

						hr = pNSM->get_INetSharingConfigurationForINetConnection(pNC, &pNSC);
						if (hr != S_OK) throw L"get_INetSharingConfigurationForINetConnection����ʧ�ܡ�";
						VARIANT_BOOL SharingEnabled;
						SHARINGCONNECTIONTYPE SharingConnectionType;
						pNSC->get_SharingEnabled(&SharingEnabled);
						pNSC->get_SharingConnectionType(&SharingConnectionType);
						if (!SharingEnabled) {
							SharingType_old = SharingType = SharingType_None;
						}
						else {
							if (SharingConnectionType == ICSSHARINGTYPE_PUBLIC) SharingType_old = SharingType = SharingType_Public;
							if (SharingConnectionType == ICSSHARINGTYPE_PRIVATE) SharingType_old = SharingType = SharingType_Private;
						}

						(*Proc)(&NetConnectionInfo, &SharingType, &ConnectingAction);

						try {
							switch (SharingType)
							{
							case SharingType_None:
								if (SharingType_old != SharingType_None) {
									hr = pNSC->DisableSharing();
									if (hr != S_OK) throw L"DisableSharing����ʧ�ܡ�";
								}
								break;
							case SharingType_Private:
								if (SharingType_old != SharingType_Private) {
									hr = pNSC->EnableSharing(ICSSHARINGTYPE_PRIVATE);
									if (hr != S_OK) throw L"EnableSharing(ICSSHARINGTYPE_PRIVATE)����ʧ�ܡ�";
								}
								break;
							case SharingType_Public:
								if (SharingType_old != SharingType_Public) {
									hr = pNSC->EnableSharing(ICSSHARINGTYPE_PUBLIC);
									if (hr != S_OK) throw L"EnableSharing(ICSSHARINGTYPE_PUBLIC)����ʧ�ܡ�";
								}
								break;
							default:
								break;
							}

							switch (ConnectingAction)
							{
							case ConnectingAction_None:
								break;
							case ConnectingAction_Connect:
								if (pNC->Connect() != S_OK) throw L"Connect����ʧ��";
								break;
							case ConnectingAction_Disconnect:
								if (pNC->Disconnect() != S_OK) throw L"Disconnect����ʧ��";
								break;
							default:
								break;
							}
						}
						catch (char *Msg) {
							//pNSC->Release();
							//pNC->Release();
							//pEV->Release();
							//pUnk->Release();
							//pNSECC->Release();
							//pNSM->Release();
							throw Msg;
						}

						//pNSC->Release();
						//pNC->Release();
					}
				}
			}

		}
		//pEV->Release();
		//pUnk->Release();
		//pNSECC->Release();
		//pNSM->Release();

		CoUninitialize();

	}



	void SetWlanPowerState(bool PowerOn)
	{
		DWORD dwResult = 0;
		DWORD dwMaxClient = 2;
		DWORD dwCurVersion = 0;
		HANDLE hClient = NULL;
		PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
		PWLAN_INTERFACE_INFO pIfInfo = NULL;

		dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
		if (dwResult != ERROR_SUCCESS) {
			throw "WlanOpenHandle����ʧ�ܡ�";
		}

		dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
		if (dwResult != ERROR_SUCCESS) {
			throw "WlanEnumInterfaces����ʧ�ܡ�";

		}


		DWORD DataSize;
		WLAN_PHY_RADIO_STATE *state;
		dwResult = WlanQueryInterface(hClient, &pIfList->InterfaceInfo[0].InterfaceGuid, wlan_intf_opcode_radio_state, NULL, &DataSize, (PVOID*)&state, NULL);

		state->dwPhyIndex = 0;
		state->dot11SoftwareRadioState = PowerOn ? dot11_radio_state_on : dot11_radio_state_off;

		if (state->dot11HardwareRadioState == state->dot11SoftwareRadioState) return;
		dwResult = WlanSetInterface(hClient, &pIfList->InterfaceInfo[0].InterfaceGuid,
			wlan_intf_opcode_radio_state, sizeof(WLAN_PHY_RADIO_STATE), state, NULL);

		WlanFreeMemory(state);

		if (dwResult != ERROR_SUCCESS) {
			throw "WlanSetInterface����ʧ�ܡ�";
		}

	}

}