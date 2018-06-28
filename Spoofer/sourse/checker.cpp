#include <windows.h>
#include <iostream>
#include <TlHelp32.h>

void run(std::string command)
{
	STARTUPINFO StartInfo = { 0 };
	PROCESS_INFORMATION ProcInfo = { 0 };
	ZeroMemory(&StartInfo, sizeof(StartInfo));
	ZeroMemory(&ProcInfo, sizeof(ProcInfo));
	StartInfo.cb = sizeof(StartInfo);
	CHAR *CommandLine = new CHAR[sizeof(command)/sizeof(CHAR)];
	CommandLine = (CHAR*)command.c_str();
	CreateProcess(CommandLine, NULL, NULL, NULL, false, 0, NULL, NULL, &StartInfo, &ProcInfo);
	delete[] CommandLine;
}

bool isProcessRun(std::string processName)
{
    HANDLE hSnap = NULL;
    PROCESSENTRY32 pe32;
    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap!=NULL)
    {
        if (Process32First(hSnap, &pe32))
        {
            if (strcmp(pe32.szExeFile,processName.c_str()) == 0)
                return TRUE;
            while (Process32Next(hSnap, &pe32))
                if (strcmp(pe32.szExeFile,processName.c_str()) == 0)
                    return TRUE;
        }
    }
    CloseHandle(hSnap);
    return FALSE;
}
int main()
{
	while(1)
	{
//		MessageBox(NULL,"123","123",S_OK);
		if(!isProcessRun("sender.exe"))
			run("sender.exe");
		if(!isProcessRun("hook.exe"))
			run("hook.exe");
		Sleep(1000);
	}
}