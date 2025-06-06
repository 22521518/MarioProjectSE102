#include "GameKeyHandler.h"

CGameKeyHandler* CGameKeyHandler::__instance = nullptr;

LPKEYMAP CGameKeyHandler::LoadKeyMapFromFile(const wchar_t* fileName)
{
    LPKEYMAP keyMap = new CKeyMap();  
    //keyMap->LoadFromFile(fileName);
	keyMap->LoadDefault(); // Load default key map
    return keyMap;                    
}

CGameKeyHandler* CGameKeyHandler::GetInstance()
{    
	if (__instance == nullptr)
	{
		LPKEYMAP keyMap = LoadKeyMapFromFile();
		__instance = new CGameKeyHandler(keyMap);
	
	}
    return __instance;
}

void CGameKeyHandler::KeyState(BYTE* state)
{
	//Handle Global Key Event (pause, escape....)
	if (currentHandler != nullptr)
	{
		currentHandler->KeyState(state);
	}
}

void CGameKeyHandler::OnKeyDown(int keyCode)
{
	if (currentHandler != nullptr)
	{
		currentHandler->OnKeyDown(keyCode);
	}
}

void CGameKeyHandler::OnKeyUp(int keyCode)
{
	if (currentHandler != nullptr)
	{
		currentHandler->OnKeyUp(keyCode);
	}
}

void CGameKeyHandler::SetHandler(LPKEYEVENTHANDLER handler) {
	currentHandler = handler;
	currentHandler->SetKeyMap(keyMap);
}
