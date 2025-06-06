#pragma once

#include <Windows.h>

#include "KeyMap.h"
/*
	Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
protected:
	LPKEYMAP keyMap = nullptr;

public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;

	void SetKeyMap(LPKEYMAP keyMap) { this->keyMap = keyMap; }
};

typedef CKeyEventHandler* LPKEYEVENTHANDLER;
