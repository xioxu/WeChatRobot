#pragma once
#include <string>

void HookChatRecord();		//HOOK�����¼
void RecieveWxMesage();		//����΢����Ϣ
void __stdcall SendWxMessage(DWORD r_eax);		//����΢����Ϣ���ͻ���
std::wstring GetMsgByAddress(DWORD memAddress);	//�ӵ�ַ�л�ȡ��Ϣ����
