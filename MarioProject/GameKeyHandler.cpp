#include "GameKeyHandler.h"

CGameKeyHandler* CGameKeyHandler::__instance = NULL;

LPKEYMAP CGameKeyHandler::LoadKeyMapFromFile(const wchar_t* fileName)
{
    LPKEYMAP keyMap = new CKeyMap();  
    //keyMap->LoadFromFile(fileName);
	keyMap->LoadDefault(); // Load default key map
    return keyMap;                    
}

CGameKeyHandler* CGameKeyHandler::GetInstance()
{    
	if (__instance == NULL)
	{
		LPKEYMAP keyMap = LoadKeyMapFromFile();
		__instance = new CGameKeyHandler(keyMap);
	
	}
    return __instance;
}

void CGameKeyHandler::KeyState(BYTE* state)
{
	//Handle Global Key Event (pause, escape....)
	if (currentHandler != NULL)
	{
		currentHandler->KeyState(state);
	}
}

void CGameKeyHandler::OnKeyDown(int keyCode)
{
	if (currentHandler != NULL)
	{
		currentHandler->OnKeyDown(keyCode);
	}
}

void CGameKeyHandler::OnKeyUp(int keyCode)
{
	if (currentHandler != NULL)
	{
		currentHandler->OnKeyUp(keyCode);
	}
}

void CGameKeyHandler::SetHandler(LPKEYEVENTHANDLER handler) {
	currentHandler = handler;
	currentHandler->SetKeyMap(keyMap);
}
