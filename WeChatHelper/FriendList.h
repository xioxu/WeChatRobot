#pragma once

void HookGetFriendList();		//HOOK��ȡ�����б��call
void GetUserListInfo();		    //��ȡ�����б�
void __stdcall SendUserListInfo(DWORD r_esi);		//���ͺ����б�
void SendTextMessage(wchar_t* wxid, wchar_t* msg);	//�����ı���Ϣ
void SendFileMessage(wchar_t* wxid, wchar_t* filepath);	//�����ļ���Ϣ
void SendImageMessage(wchar_t* wxid, wchar_t* filepath);//����ͼƬ��Ϣ
void DeleteUser(wchar_t* wxid);	//ɾ������
void SendXmlCard(wchar_t* RecverWxid, wchar_t* SendWxid, wchar_t* NickName); //����XML��Ƭ
std::string wstringToString(const std::wstring& wstr);
wchar_t* GetNicknameByWxid(wchar_t* userwxid);
wstring GetNickNameByWxid(wstring wxid);

