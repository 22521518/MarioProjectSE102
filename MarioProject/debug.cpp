#include "debug.h"
#include "GameObject.h"

#include <typeinfo>

HWND _hwnd = NULL;

void DebugOut(const wchar_t* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

void DebugOutObjectClassName(LPGAMEOBJECT obj)
{
	std::string className = std::string(typeid(*obj).name());
	std::wstring wClassName(className.begin(), className.end());
	DebugOut(L"Name %s\n", wClassName.c_str());
}



void DebugOutTitle(const wchar_t* fmt, ...)
{
	wchar_t s[1024];
	VA_PRINTS(s);
	SetWindowText(_hwnd, s);
}

void SetDebugWindow(HWND hwnd)
{
	_hwnd = hwnd;
}