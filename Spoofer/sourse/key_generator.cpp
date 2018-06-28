#include <iostream>
#include <ctime>
#include <cstring>
#include <windows.h>
using namespace std;

int random(int min,int max);
void toClipboard(const char* text);

int main()
{
	string login;
	string password;
	string key;
	char tmp[7];
	int rnd;
	
	cin>>login>>password;
	rnd = random(101,999);
	
	for(int i = 0; i < login.size();i++)
	{
		sprintf(tmp,"%06d",login[i]*rnd);
		key += tmp;
	}
	sprintf(tmp,"%06d",":"[0] * rnd);
		key += tmp;
	for(int i = 0; i < password.size();i++)
	{
		sprintf(tmp,"%06d",password[i]*rnd);
		key += tmp;
	}
	sprintf(tmp,"%d",rnd);
	key += tmp;
	toClipboard(key.c_str());
}

int random(int min,int max)
{
	max++;
	SYSTEMTIME st;
    GetLocalTime(&st);
	srand(st.wMilliseconds*1111+10000);
	return min + rand() % (max - min);
}

void toClipboard(const char* text)
{
    if(OpenClipboard(0))
    {
        EmptyClipboard();
        char* clip_data = (char*)(GlobalAlloc(GMEM_FIXED, MAX_PATH));
        lstrcpy(clip_data, text);
        SetClipboardData(CF_TEXT, (HANDLE)(clip_data));
        LCID* lcid = (DWORD*)(GlobalAlloc(GMEM_FIXED, sizeof(DWORD)));
        *lcid = MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_NEUTRAL), SORT_DEFAULT);
        SetClipboardData(CF_LOCALE, (HANDLE)(lcid));
        CloseClipboard();
    }
}