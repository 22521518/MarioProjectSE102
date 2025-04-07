#pragma once

#include "KeyEventHandler.h"
#include "Scene.h"

class CSceneKeyHandler : public CKeyEventHandler
{
protected:
	CScene* scence;

public:
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler(), scence(s) {}

	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;