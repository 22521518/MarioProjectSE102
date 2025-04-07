#pragma once

#include "SceneKeyHandler.h"
#include "KeyMap.h"
#include "Game.h"
#include "debug.h"

class CPlayScene;
typedef CPlayScene* LPPLAYSCENE;

class CMario;
typedef CMario* LPMARIO;

class CMarioPlayerKeyHandler : public CSceneKeyHandler
{
	LPMARIO mario = NULL;
public:
    CMarioPlayerKeyHandler(LPPLAYSCENE s);

    void KeyState(BYTE* states);
    void OnKeyDown(int KeyCode);
    void OnKeyUp(int KeyCode);

	void SetMario(LPMARIO m) { this->mario = m; }
};

typedef CMarioPlayerKeyHandler* LPMARIOPLAYERKEYHANDLER;