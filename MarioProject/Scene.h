#pragma once

#include "KeyEventHandler.h"

class CScene
{
protected:
	LPKEYEVENTHANDLER keyHandler = NULL;
	int id;
	LPCWSTR sceneFilePath;

public:
	CScene(int id, LPCWSTR filePath) : id(id), sceneFilePath(filePath) {}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	LPKEYEVENTHANDLER GetKeyEventHandler() const { return keyHandler; }
};

typedef CScene* LPSCENE;
