#pragma once
#include <string>
#include "easywsclient.hpp"
using namespace std;

extern easywsclient::WebSocket::pointer p_ws;
std::string To_byte_string(const std::wstring& input);
void ConnWS();
void HookAnyAddress(DWORD dwHookAddr, LPVOID dwJmpAddress);		//HOOK任意地址

DWORD GetWeChatWinBase();		//获取WeChatWin基址

wchar_t * UTF8ToUnicode(const char* str);

wstring UTF8ToUnicode2(const char* str);
string UnicodeToUtf82(const std::wstring& wstr);

void DebugCode(LPVOID pAddress);