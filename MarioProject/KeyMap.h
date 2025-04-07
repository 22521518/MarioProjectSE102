#pragma once

#include <Windows.h>
#include <unordered_map>
#include <string>
#include <dinput.h>
#include <fstream>

#include "stringUtil.h"
using namespace std;

enum class ActionKey
{
    MoveLeft,
    MoveRight,
    Jump,
    Sit,
    Pause,
    Reload,
    SetSmall,
	SetBig,
    SetDie,
    Run,
};

class CKeyMap
{
	unordered_map<ActionKey, int> keyMap;
public:
    void SetKey(ActionKey action, int keyCode);
    int GetKey(ActionKey action);
    bool IsActionPressed(BYTE* states, ActionKey action);
    void LoadDefault(); 
    void SaveToFile(const string& filename);
    void LoadFromFile(const wstring& filename);

    ~CKeyMap();
};

typedef CKeyMap* LPKEYMAP;