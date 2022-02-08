#include "stdafx.h"
#include "Login.h"


DWORD dwRetAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxQrCodeOffset + 5;	//���ص�ַ
DWORD dwOverAddr = (DWORD)GetModuleHandle(L"WeChatWin.dll") + WxQrCodeOffsetCall;	//���ǵ�call


//************************************************************
// ��������: HookQrCode
// ����˵��: HOOK΢�Ŷ�ά��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: DWORD dwHookOffset Ҫhook��ƫ�� 
// �� �� ֵ: void
//************************************************************
void HookQrCode()
{
	HookAnyAddress(GetWeChatWinBase()+ WxQrCodeOffset, ShowPic);
}


//************************************************************
// ��������: ShowPic
// ����˵��: ��ʾ��ά��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/16
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void  __declspec(naked) ShowPic()
{
	__asm
	{
		pushad;
		pushfd;
		push ecx;
		call SaveImg;
		popfd;
		popad;
		call dwOverAddr;
		jmp dwRetAddr;
	}
}


//************************************************************
// ��������: SaveImg
// ����˵��: �����ά��ͼƬ
// ��    ��: GuiShou
// ʱ    ��: 2019/6/30
// ��    ��: DWORD qrcode ��ά��ͼƬ���ڵĵ�ַ
// �� �� ֵ: void
//************************************************************
void __stdcall SaveImg(DWORD qrcode)
{
	//��ȡͼƬ����
	DWORD dwPicLen = qrcode + 0x4;
	size_t cpyLen = (size_t)*((LPVOID*)dwPicLen);
	//����ͼƬ������
	char PicData[0xFFF] = { 0 };
	memcpy(PicData, *((LPVOID*)qrcode), cpyLen);

	char szTempPath[MAX_PATH] = { 0 };
	char szPicturePath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, szTempPath);

	sprintf_s(szPicturePath, "%s%s", szTempPath, "qrcode.png");
	//���ļ�д��TempĿ¼��
	HANDLE hFile = CreateFileA(szPicturePath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL)
	{
		OutputDebugStringA("����ͼƬ�ļ�ʧ��");
		return;
	}

	DWORD dwRead = 0;
	if (WriteFile(hFile, PicData, cpyLen, &dwRead, NULL) == 0)
	{
		OutputDebugStringA("д��ͼƬ�ļ�ʧ��");
		return;
	}
	CloseHandle(hFile);
}



//************************************************************
// ��������: GotoQrCode
// ����˵��: ��ת����ά�봰��
// ��    ��: GuiShou
// ʱ    ��: 2019/6/16
// ��    ��: void
// �� �� ֵ: void
//************************************************************
void GotoQrCode()
{
	DWORD dwBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwCallAddr1 = dwBaseAddress + WxGoToQrCode1;
	DWORD dwCallAddr2 = dwBaseAddress + WxGoToQrCode2;

	__asm 
	{
		call dwCallAddr1;
		mov ecx, eax;
		call dwCallAddr2;
	}
}

