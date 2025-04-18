#pragma once

#include <windows.h>
#include <signal.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <typeinfo>

#define _W(x)  __W(x)
#define __W(x)  L##x

#define VA_PRINTS(s) {				\
		va_list argp;				\
		va_start(argp, fmt);		\
		vswprintf_s(s, fmt, argp);	\
		va_end(argp);				\
}

using namespace std;

void DebugOut(const wchar_t* fmt, ...);
void DebugOutTitle(const wchar_t* fmt, ...);
void SetDebugWindow(HWND hwnd);

template<typename T>
void DebugOutObjectClassName(T* obj)
{
	if (obj)
	{
		string className = typeid(*obj).name(); 
		wstring wClassName(className.begin(), className.end());
		OutputDebugStringW((L"Name: " + wClassName + L"\n").c_str());
	}
	else
	{
		OutputDebugStringW(L"Null pointer received\n");
	}
}