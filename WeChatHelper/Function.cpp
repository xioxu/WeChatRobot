#include "stdafx.h"
#include "Function.h"
#include <stdlib.h >
#include <vector>
#include "FriendList.h"

vector<wstring> g_wxidgroup;			//���嶯̬������΢��ID




//************************************************************
// ��������: AddWxUser
// ����˵��: ��Ӻ���
// ��    ��: GuiShou
// ʱ    ��: 2019/7/13
// ��    ��: wxid ΢��ID msg��Ӻ���ʱҪ���͵���Ϣ
// �� �� ֵ: void 
//************************************************************
void AddWxUser(wchar_t* wxid, wchar_t* msg)
{
	DWORD dwWeChatWinAddr = GetWeChatWinBase();
	DWORD dwParam1 = dwWeChatWinAddr + WxAddWxUserParam1;
	DWORD dwCall1 = dwWeChatWinAddr + WxAddWxUserCall1;
	DWORD dwCall2 = dwWeChatWinAddr + WxAddWxUserCall2;
	DWORD dwCall3 = dwWeChatWinAddr + WxAddWxUserCall3;
	DWORD dwCall4 = dwWeChatWinAddr + WxAddWxUserCall4;
	DWORD dwCall5 = dwWeChatWinAddr + WxAddWxUserCall5;

	GeneralStruct pWxid(wxid);
	GeneralStruct pMsg(msg);

	char* asmWxid = (char*)&pWxid.pstr;
	char* asmMsg = (char*)&pMsg.pstr;
	DWORD asmMsgText = (DWORD)pMsg.pstr;
	char buff3[0x100] = { 0 };
	char* buff = buff3;
	__asm
	{
		sub esp, 0x18;
		mov ecx, esp;
		push  dwParam1;
		call dwCall1;

		sub esp, 0x18;
		mov eax, buff;
		mov ecx, esp;
		push eax;
		call dwCall2;

		push 0x6;
		sub esp, 0x14;
		mov ecx, esp;
		push -0x1;
		mov edi, msg;
		push edi;
		call dwCall3;


		push 0x2;
		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, asmWxid;
		push ebx;
		call dwCall4;

		mov ecx, eax;
		call dwCall5;
	}
}



//************************************************************
// ��������: OpenUrl
// ����˵��: ��΢�������
// ��    ��: GuiShou
// ʱ    ��: 2019/9/10
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void OpenUrl(wchar_t* Url)
{
	GeneralStruct pUrl(Url);
	char* asmpUrl = (char*)&pUrl.pstr;
	DWORD dwWeChatWinAddr = GetWeChatWinBase();
	DWORD callAdd1 = dwWeChatWinAddr + WxOpenUrlCall1;
	DWORD callAdd2 = dwWeChatWinAddr + WxOpenUrlCall2;
	__asm {
		pushad
		sub esp, 0x14
		mov eax, asmpUrl
		mov ecx, esp
		push eax
		call callAdd1
		call callAdd2
		add esp, 0x14
		popad
	}
}



//************************************************************
// ��������: AntiRevoke
// ����˵��: ������
// ��    ��: GuiShou
// ʱ    ��: 2019/7/15
// ��    ��: void
// �� �� ֵ: void 
//************************************************************
void AntiRevoke()
{
	unsigned char fix[1] = { 0xEB };
	DWORD dwPathcAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxAntiRevoke;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 1, PAGE_EXECUTE_READWRITE, &dwOldAttr);

	//Patch
	memcpy((LPVOID)dwPathcAddr, fix, 1);

	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}