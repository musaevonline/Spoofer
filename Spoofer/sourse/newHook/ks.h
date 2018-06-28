#ifndef KS_H
#define KS_H

#include <windows.h>
#include <stdio.h>

#ifdef __DLL__
#define DLL_EI __declspec(dllexport)
#else
#define DLL_EI __declspec(dllimport)
#endif
//---------------------------------------------------------------------------
extern "C" {
LRESULT CALLBACK DLL_EI HksKeyProc(int nCode, WPARAM wParam, LPARAM lParam);
void DLL_EI HksInit();
void DLL_EI HksClose();
};
//---------------------------------------------------------------------------

#endif