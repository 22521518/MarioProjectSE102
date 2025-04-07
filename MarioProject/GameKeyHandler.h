#pragma once
#include "KeyEventHandler.h"
#include "MarioPlayerKeyHandler.h"
#include "KeyMap.h"

#define KEYMAP_FILE L"keymap.txt"

class CGameKeyHandler :
    public CKeyEventHandler
{
	static CGameKeyHandler* __instance;

	LPKEYEVENTHANDLER currentHandler = NULL;
	LPKEYMAP keyMap = NULL;

	CGameKeyHandler(LPKEYMAP keyMap) {
		this->keyMap = keyMap;
		this->currentHandler = NULL;
	}
	CGameKeyHandler(LPKEYMAP keyMap, LPKEYEVENTHANDLER handler) : keyMap(keyMap), currentHandler(handler) {}
	static LPKEYMAP LoadKeyMapFromFile(const wchar_t* fileName = KEYMAP_FILE);

public:
	
	static CGameKeyHandler* GetInstance();
	void SetHandler(LPKEYEVENTHANDLER handler);

	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	
	LPKEYEVENTHANDLER GetHandler() const { return this->currentHandler; }
};

typedef CGameKeyHandler* LPGAMEKEYHANDLER;
