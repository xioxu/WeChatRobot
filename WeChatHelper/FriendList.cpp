#include "stdafx.h"
#include "FriendList.h"
#include "shellapi.h"
#include <sstream>
#include <iomanip>
#include <strstream>
#include <map>
#include <iostream>
#include <fstream>
#include "ChatRecord.h"
#pragma comment(lib, "Version.lib")


//�������к����б��map����
map<wstring, wstring> g_userinfolist;

DWORD overWritedCallAdd= GetWeChatWinBase() + WxFriendListCall;

DWORD jumBackAddress= GetWeChatWinBase() + WxFriendList+5;

//�Ƽ����б�
wstring g_referencenumber[11] =
{
	L"fmessage",L"qqmail",L"medianote",L"qmessage",L"newsapp",L"filehelper"
	L"weixin", L"tmessage", L"mphelper",L"gh_7aac992b0363", L"qqsafe"
};

//************************************************************
// ��������: HookGetFriendList
// ����˵��: HOOK��ȡ�����б��call 
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void HookGetFriendList()
{
	HookAnyAddress(GetWeChatWinBase() + WxFriendList, GetUserListInfo);
}



//************************************************************
// ��������: GetUserListInfo
// ����˵��: ��ȡ�û���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
__declspec(naked) void GetUserListInfo()
{
	__asm
	{
		pushad;
		push esi;
		call SendUserListInfo;
		popad;

		//���䱻���ǵĴ���
		call overWritedCallAdd;

		//���ر�HOOKָ�����һ��ָ��
		jmp jumBackAddress
	}
}

//************************************************************
// ��������: ReSendUser
// ����˵��: �ٴη��ͺ�����Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: user
// �� �� ֵ: void 
//************************************************************
void ReSendUser(UserListInfo* user)
{
	HWND hWnd = NULL;
	while (true)
	{
		//���͵����ƶ�
		hWnd = FindWindow(NULL, TEXT("΢������"));
		if (hWnd == NULL)
		{
			Sleep(200);
			continue;
		}
		break;
	}

	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//����һ����ֵ, ������������־��
	userinfo.cbData = sizeof(UserListInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfo.lpData = user;// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
	delete user;
}




//************************************************************
// ��������: SendUserListInfo
// ����˵��: ���ͺ����б�
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: r_esi �����б����ڵ�����ָ��
// �� �� ֵ: void 
//************************************************************
void __stdcall SendUserListInfo(DWORD r_esi)
{
	//����΢�źš�Ⱥ��
	wstring wxid = GetMsgByAddress(r_esi + 0x8);
	wstring nickname = GetMsgByAddress(r_esi + 0x64);

	//�����б�ȥ��
	map<wstring, wstring>::iterator it;
	it = g_userinfolist.find(wxid);
	//�������ֵ������end() ˵���ҵ��� ֱ�ӷ��ط�ֹ�ظ�
	if (it != g_userinfolist.end())
	{
		return;
	}
	//���û���ҵ� ����뵽����
	g_userinfolist.insert(make_pair(wxid, nickname));

	//�ų��Ƽ����б�
	for (int i = 0; i < 11; i++)
	{
		if (g_referencenumber[i] == wxid)
		{
			return;
		}
	}


	unique_ptr<UserListInfo> user(new UserListInfo);

	LPVOID pUserWxid = *((LPVOID *)(r_esi + 0x8));		//΢��ID
	LPVOID pUserNumber = *((LPVOID *)(r_esi + 0x1C));	//΢�ź�
	LPVOID pUserNick = *((LPVOID *)(r_esi + 0x64));		//�ǳ�
	LPVOID pUserReMark = *((LPVOID *)(r_esi + 0x50));	//��ע

	swprintf_s(user->UserId, L"%s", (wchar_t*)pUserWxid);
	swprintf_s(user->UserNumber, L"%s", (wchar_t*)pUserNumber);
	swprintf_s(user->UserNickName, L"%s", (wchar_t*)pUserNick);
	swprintf_s(user->UserRemark, L"%s", (wchar_t*)pUserReMark);


	//���͵����ƶ�
	HWND hWnd = FindWindow(NULL, TEXT("΢������"));
	if (hWnd == NULL)
	{
		UserListInfo* outuser = new UserListInfo;
	
		swprintf_s(outuser->UserId, L"%s", (wchar_t*)pUserWxid);
		swprintf_s(outuser->UserNumber, L"%s", (wchar_t*)pUserNumber);
		swprintf_s(outuser->UserNickName, L"%s", (wchar_t*)pUserNick);
		swprintf_s(outuser->UserRemark, L"%s", (wchar_t*)pUserReMark);
	
	
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReSendUser, outuser, 0, NULL);
		CloseHandle(hThread);
	}
	
	COPYDATASTRUCT userinfo;
	userinfo.dwData = WM_GetFriendList;//����һ����ֵ, ������������־��
	userinfo.cbData = sizeof(UserListInfo);// strlen(szSendBuf);//�����͵����ݵĳ�
	userinfo.lpData = user.get();// szSendBuf;//�����͵����ݵ���ʼ��ַ(����ΪNULL)
	SendMessage(hWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&userinfo);
}



//************************************************************
// ��������: SendTextMessage
// ����˵��: �����ı���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: wxid ΢��ID msg��Ϣ����
// �� �� ֵ: void 
//************************************************************
void SendTextMessage(wchar_t* wxid, wchar_t* msg)
{
	//�õ�������Ϣ��call�ĵ�ַ
	DWORD dwSendCallAddr = GetWeChatWinBase() + WxSendMessage;

	//��װ΢��ID/ȺID�Ľṹ��
	GeneralStruct id(wxid);
	//��Ϣ����
	GeneralStruct text(msg);

	//ȡ��΢��ID����Ϣ�ĵ�ַ
	char* pWxid = (char*)&id.pstr;
	char* pWxmsg = (char*)&text.pstr;

	char buff[0x81C] = { 0 };
	char buff2[0x81C] = { 0 };

	//����΢�ŷ�����Ϣcall
	__asm {
		push 0x1;
		lea edi, buff2;
		push edi;
		mov ebx, pWxmsg;
		push ebx;
		lea ecx, buff;
		mov edx, pWxid;
		call dwSendCallAddr;
		add esp, 0xC;
	}
}


//************************************************************
// ��������: SendFileMessage
// ����˵��: �����ļ���Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/4
// ��    ��: wxid ΢��ID filepath �ļ�·��
// �� �� ֵ: void 
//************************************************************
void SendFileMessage(wchar_t* wxid, wchar_t* filepath)
{
	//������Ҫ�ĵ�ַ
	DWORD dwBase = GetWeChatWinBase();
	DWORD dwCall1 = dwBase + WxFileMessage1;
	DWORD dwCall2 = dwBase + WxFileMessage2;
	DWORD dwCall3 = dwBase + WxFileMessage3;	//�������
	DWORD dwCall4 = dwBase + WxFileMessage4;	//������Ϣ
	DWORD dwParams = dwBase + WxFileMessageParam;

	char buff[0x528] = { 0 };

	//������Ҫ������
	GeneralStruct wxidStruct(wxid);
	GeneralStruct filePathStruct(filepath);

	//ȡ����Ҫ�����ݵĵ�ַ
	char* pFilePath = (char*)&filePathStruct.pstr;
	char* pWxid = (char*)&wxidStruct.pstr;



	__asm {
		pushad;
		sub esp, 0x14;
		lea eax, buff;
		mov ecx, esp;
		push eax;
		call dwCall2;

		push 0;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		push dwParams;
		call dwCall1;

		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, pFilePath;
		push ebx;
		call dwCall2;

		sub esp, 0x14;
		mov eax, pWxid;
		mov ecx, esp;
		push eax;
		call dwCall2;

		lea eax, buff;
		push eax;
		call dwCall3;

		mov ecx, eax;
		call dwCall4;
		popad;
	}
}



//************************************************************
// ��������: SendImageMessage
// ����˵��: ����ͼƬ��Ϣ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/7
// ��    ��: wxid ΢��ID filepath ͼƬ·��
// �� �� ֵ: void 
//************************************************************
void SendImageMessage(wchar_t* wxid, wchar_t* filepath)
{
	//��װ΢��ID�����ݽṹ
	GeneralStruct imagewxid(wxid);
	//��װ�ļ�·�������ݽṹ
	GeneralStruct imagefilepath(filepath);
	char buff[0x528] = { 0 };
	char buff2[0x60] = { 0 };


	DWORD dwCall3 = GetWeChatWinBase() + WxSendImageCall3;
	DWORD dwCall1 = GetWeChatWinBase()+ WxSendImageCall1;
	DWORD dwCall2 = GetWeChatWinBase() + WxSendImageCall2;


	//΢�ŷ���ͼƬ������GidCreateBimapFileCM ֮��ͼƬһֱ��ռ�� �޷�ɾ�� patch������Ĵ���
	unsigned char oldcode[5] = {0};
	unsigned char fix[5] = { 0x31,0xC0,0x90,0x90,0x90 };
	DWORD dwPathcAddr = GetWeChatWinBase() + WxPatchAddr;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//�ȱ���ԭ��ָ��
	memcpy(oldcode, (LPVOID)dwPathcAddr, 5);
	//��Patch��
	memcpy((LPVOID)dwPathcAddr, fix, 5);


	__asm
	{
		pushad;
		sub esp, 0x14;
		lea eax, buff2;
		mov ecx, esp;
		push eax;
		call dwCall3;
		lea ebx, imagefilepath;
		push ebx;
		lea eax, imagewxid;
		push eax;
		lea eax, buff;
		push eax;
		call dwCall1;
		mov ecx, eax;
		call dwCall2;
		popad;
	}
	//������֮��ָ�
	memcpy((LPVOID)dwPathcAddr, oldcode, 5);
	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}


//************************************************************
// ��������: WxDeleteUser
// ����˵��: ɾ������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/8
// ��    ��: wxid ΢��ID
// �� �� ֵ: void 
//************************************************************
void DeleteUser(wchar_t* wxid)
{
	DWORD dwBaseAddress = GetWeChatWinBase();
	//��������
	GeneralStruct structWxid(wxid);
	DWORD* asmMsg = (DWORD*)&structWxid.pstr;
	DWORD dwCallAddr = dwBaseAddress + WxDeleteUser;

	__asm 
	{
		mov ecx, 0;
		push ecx;
		mov esi, asmMsg;
		push esi;
		call  dwCallAddr;
	}
}


//************************************************************
// ��������: SendXmlCard
// ����˵��: ����XML��Ƭ
// ��    ��: GuiShou
// ʱ    ��: 2019/7/10
// ��    ��: RecverWxid ������΢��ID SendWxidҪ���͵�΢��ID NickName΢���ǳ�
// �� �� ֵ: void 
//************************************************************
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName)
{
	wchar_t xml[0x2000] = { 0 };
	swprintf_s(xml, L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/132\" username=\"%s\" nickname=\"%s\" fullpy=\"?\" shortpy=\"\" alias=\"%s\" imagestatus=\"3\" scene=\"17\" province=\"����\" city=\"�й�\" sign=\"\" sex=\"2\" certflag=\"0\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"0\" regionCode=\"CN_BeiJing_BeiJing\" />", SendWxid, NickName, SendWxid);
	GeneralStruct pWxid(RecverWxid);
	GeneralStruct pXml(xml);


	char* asmWxid = (char *)&pWxid.pstr;
	char* asmXml = (char *)&pXml.pstr;
	char buff[0x20C] = { 0 };
	DWORD callAdd = GetWeChatWinBase() + WxSendXmlCard;


	__asm {
		mov eax, asmXml
		push 0x2A
		mov edx, asmWxid
		push 0x0
		push eax
		lea ecx, buff
		call callAdd
		add esp, 0xC
	}
}



//************************************************************
// ��������: wstringToString
// ����˵��: ��wstringת��String
// ��    ��: GuiShou
// ʱ    ��: 2019/9/17
// ��    ��: wstr
// �� �� ֵ: string 
//************************************************************
std::string wstringToString(const std::wstring& wstr)
{
	LPCWSTR pwszSrc = wstr.c_str();
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
		return std::string("");

	char* pszDst = new char[nLen];
	if (!pszDst)
		return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	std::string str(pszDst);
	delete[] pszDst;
	pszDst = NULL;
	return str;
}




//************************************************************
// ��������: GetNickNameByWxid
// ����˵��: ���ݺ����б��΢��ID/ȺID����ȡ΢���ǳ�/Ⱥ�ǳ�
// ��    ��: GuiShou
// ʱ    ��: 2020/2/10
// ��    ��: nickname �ǳ�
// �� �� ֵ: void 
//************************************************************
wstring GetNickNameByWxid(wstring wxid)
{
	map<wstring, wstring>::iterator it;
	it = g_userinfolist.find(wxid);
	if (it != g_userinfolist.end())
	{
		return it->second;
	}
	else
	{
		return L"NULL";
	}
}


//************************************************************
// ��������: GetNicknameByWxid
// ����˵��: ����΢��ID��ȡ�ǳ�
// ��    ��: GuiShou
// ʱ    ��: 2020/2/10
// ��    ��: wxid ΢��ID
// �� �� ֵ: wchar_t* �ǳ� 
//************************************************************
wchar_t* GetNicknameByWxid(wchar_t* userwxid)
{
	DWORD dwCall1 = GetWeChatWinBase() + WxGetUserInfoByWxidCall1;
	DWORD dwCall2 =  GetWeChatWinBase() + WxGetUserInfoByWxidCall2;
	DWORD dwCall3 =  GetWeChatWinBase() + WxGetUserInfoByWxidCall3;

	GeneralStruct pWxid(userwxid);
	char* asmWxid = (char*)& pWxid.pstr;
	char buff[0x3D8] = { 0 };
	DWORD userData = 0;		//�û����ݵĵ�ַ
	__asm
	{
		pushad;
		lea edi, buff;
		push edi;
		sub esp, 0x14;
		mov eax, asmWxid;
		mov ecx, esp;
		push eax;
		call dwCall1;
		call dwCall2;
		call dwCall3;
		mov userData, edi;
		popad;
	}

	wchar_t tempnickname[100] = { 0 };
	DWORD wxNickAdd = userData + 0x64;	//�ǳ�
	swprintf_s(tempnickname, L"%s", (wchar_t*)(*((LPVOID*)wxNickAdd)));

	wchar_t* nickname = new wchar_t[100]{ 0 };
	memcpy(nickname, tempnickname, wcslen(tempnickname) * 2);
	return nickname;
}
