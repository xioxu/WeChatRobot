#include "stdafx.h"
#include "SelfInformation.h"
#include "Function.h"
#include "CPublic.h"


//************************************************************
// ��������: GetSelfInformation
// ����˵��: ��ȡ������Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/12/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
//void GetInformation()
//{
//	Information *info = new Information;
//	char tempcontent[0x300];
//	//��ȡWeChatWin�Ļ�ַ
//	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll");
//
//	//΢��ID ������Ҫ��������΢�ź�  ��΢�ź���ָ�� ��΢�ź����ַ���
//	memset(tempcontent, 0, 0x300);
//	DWORD pWxid = dwWeChatWinAddr + 0x161C814;
//	//�������С��6���ߴ���20 ˵������ط��Ǹ�ָ��
//	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWinAddr + 0x161C814));
//	if (strlen(tempcontent) < 0x6 || strlen(tempcontent) > 0x14)
//	{
//		//˵�����µ�΢�ź� ΢��ID�õ�ַ����
//		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWinAddr + 0x161C814)));
//	}
//	else
//	{
//		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWinAddr + 0x161C814));
//	}
//	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode(tempcontent)) + 1, UTF8ToUnicode(tempcontent));
//
//	//΢��ID
//	//char wxid[0x1000] = { 0 };
//	//DWORD pWxid = dwWeChatWinAddr + 0x161C814;
//	//sprintf_s(wxid, "%s", (char*)(*(DWORD*)pWxid));
//	//if (strlen(wxid) < 40)
//	//{
//	//	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode(wxid)) + 1, UTF8ToUnicode(wxid));
//	//}
//	//else
//	//{
//	//	wcscpy_s(info->wxid, wcslen(L"΢��ID��ʱ�޷���ʾ") + 1, L"΢��ID��ʱ�޷���ʾ");
//	//}
//
//	//΢���Ա�
//	char sex[4] = { 0 };
//	memcpy(sex, (void*)(pWxid + 0x160), 1);
//
//	if (sex[0] == 1)
//	{
//		wcscpy_s(info->wxsex, wcslen(L"��") + 1, L"��");
//	}
//	if (sex[0] == 2)
//	{
//		wcscpy_s(info->wxsex, wcslen(L"Ů") + 1, L"Ů");
//	}
//
//	//΢���ǳ�
//	char nickname[40] = { 0 };
//	if (*(DWORD*)(pWxid + 0x78 + 0x14) == 0xF)
//	{
//		sprintf_s(nickname, "%s", (char*)(pWxid + 0x78));
//		wcscpy_s(info->nickname, wcslen(UTF8ToUnicode(nickname)) + 1, UTF8ToUnicode(nickname));
//	}
//	else
//	{
//		DWORD pNickName = pWxid + 0x78;
//		sprintf_s(nickname, "%s", (char*)(*(DWORD*)pNickName));
//		wcscpy_s(info->nickname, wcslen(UTF8ToUnicode(nickname)) + 1, UTF8ToUnicode(nickname));
//	}
//
//	//΢���˺�
//	char wxcount[40] = { 0 };
//	sprintf_s(wxcount, "%s", (char*)(pWxid + 0x1DC));
//	wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode(wxcount)) + 1, UTF8ToUnicode(wxcount));
//
//	//�ֻ���
//	char phone[40] = { 0 };
//	sprintf_s(phone, "%s", (char*)(pWxid + 0xAC));
//	wcscpy_s(info->phonenumber, wcslen(UTF8ToUnicode(phone)) + 1, UTF8ToUnicode(phone));
//
//	//��½�豸
//	char device[15] = { 0 };
//	sprintf_s(device, "%s", (char*)(pWxid + 0x4B4));
//	wcscpy_s(info->device, wcslen(UTF8ToUnicode(device)) + 1, UTF8ToUnicode(device));
//
//	//����
//	char nation[10] = { 0 };
//	sprintf_s(nation, "%s", (char*)(pWxid + 0x254));
//	wcscpy_s(info->nation, wcslen(UTF8ToUnicode(nation)) + 1, UTF8ToUnicode(nation));
//
//	//ʡ��
//	char province[20] = { 0 };
//	sprintf_s(province, "%s", (char*)(pWxid + 0x164));
//	wcscpy_s(info->province, wcslen(UTF8ToUnicode(province)) + 1, UTF8ToUnicode(province));
//
//	//����
//	char city[20] = { 0 };
//	sprintf_s(city, "%s", (char*)(pWxid + 0x17C));
//	wcscpy_s(info->city, wcslen(UTF8ToUnicode(city)) + 1, UTF8ToUnicode(city));
//
//
//	//Сͷ��
//	char header[0x100] = { 0 };
//	DWORD pHeader = pWxid + 0x358;
//	sprintf_s(header, "%s", (char*)(*(DWORD*)pHeader));
//	wcscpy_s(info->smallheader, wcslen(UTF8ToUnicode(header)) + 1, UTF8ToUnicode(header));
//
//
//	//��ͷ��
//	char bigheader[0x100] = { 0 };
//	DWORD pbigheader = pWxid + 0x340;
//	sprintf_s(bigheader, "%s", (char*)(*(DWORD*)pbigheader));
//	wcscpy_s(info->bigheader, wcslen(UTF8ToUnicode(bigheader)) + 1, UTF8ToUnicode(bigheader));
//
//	//���͵��ͻ���
//	HWND hInformation = FindWindow(NULL, L"Information");
//	if (hInformation == NULL)
//	{
//		OutputDebugStringA("δ���ҵ�Information����");
//		return;
//	}
//	COPYDATASTRUCT information_msg;
//	information_msg.dwData = WM_GetInformation;
//	information_msg.lpData = info;
//	information_msg.cbData = sizeof(Information);
//	//������Ϣ�����ƶ�
//	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
//
//	delete info;
//}



void GetInformation()
{
	unique_ptr<PersonalInformation> info(new PersonalInformation);

	DWORD dwWeChatWin = GetWeChatWinBase();

	char tempcontent[0x300];
	//΢�ź�
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxCount));

	//�ж��Ƿ�Ϊ0 ��0˵��΢�ź�Ϊ��
	if (tempcontent[0] == 0)
	{
		wcscpy_s(info->wxcount, wcslen(L"NULL") + 1, L"NULL");
	}
	else
	{
		wcscpy_s(info->wxcount, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());
	}


	//΢��ID ������Ҫ��������΢�ź�  ��΢�ź���ָ�� ��΢�ź����ַ���
	memset(tempcontent, 0, 0x300);
	DWORD pWxid = dwWeChatWin + WxID;
	//�������С��6���ߴ���20 ˵������ط��Ǹ�ָ��
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxID));
	if (strlen(tempcontent) < 0x6 || strlen(tempcontent) > 0x14)
	{
		//˵�����µ�΢�ź� ΢��ID�õ�ַ����
		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxID)));
	}
	else
	{
		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxID));
	}
	wcscpy_s(info->wxid, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//Сͷ��
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxSmallHeader)));
	wcscpy_s(info->smallheader, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());



	//��ͷ��
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxBigHeader)));
	wcscpy_s(info->bigheader, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//����
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxNation));
	wcscpy_s(info->nation, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());

	//ʡ��
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxProvince));
	wcscpy_s(info->province, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//����
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxCity));
	wcscpy_s(info->city, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//�ֻ���
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxPhoneNumber));
	wcscpy_s(info->phonenumber, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());

	//�ǳ�
	memset(tempcontent, 0, 0x300);
	if (*(DWORD*)(dwWeChatWin + WxNickName + 0x14) == 0xF)
	{
		sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxNickName));
	}
	else
	{
		sprintf_s(tempcontent, "%s", (char*)(*(DWORD*)(dwWeChatWin + WxNickName)));
	}
	
	wcscpy_s(info->nickname, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//����Ŀ¼
	swprintf_s(info->cachedir, L"%s", (wchar_t*)(*(DWORD*)(dwWeChatWin + WxCacheDir)));


	//��½�豸
	memset(tempcontent, 0, 0x300);
	sprintf_s(tempcontent, "%s", (char*)(dwWeChatWin + WxDevice));
	wcscpy_s(info->device, wcslen(UTF8ToUnicode2(tempcontent).c_str()) + 1, UTF8ToUnicode2(tempcontent).c_str());


	//�Ա�
	DWORD nSex = *(DWORD*)(dwWeChatWin + WxSex);
	if (nSex == 1)
	{
		wcscpy_s(info->wxsex, wcslen(L"��") + 1, L"��");
	}
	else if (nSex == 2)
	{
		wcscpy_s(info->wxsex, wcslen(L"Ů") + 1, L"Ů");
	}
	else
	{
		wcscpy_s(info->wxsex, wcslen(L"δ����") + 1, L"δ����");
	}


	HWND hInformation = FindWindow(NULL, L"Information");
	if (hInformation == NULL)
	{
		OutputDebugStringA("δ���ҵ�Information����");
		return;
	}
	COPYDATASTRUCT information_msg;
	information_msg.dwData = WM_GetInformation;
	information_msg.lpData = info.get();
	information_msg.cbData = sizeof(PersonalInformation);
	//������Ϣ�����ƶ�
	SendMessage(hInformation, WM_COPYDATA, (WPARAM)hInformation, (LPARAM)&information_msg);
}
