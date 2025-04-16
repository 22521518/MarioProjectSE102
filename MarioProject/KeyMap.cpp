#include "KeyMap.h"

void CKeyMap::SetKey(ActionKey action, int keyCode)
{
    keyMap[action] = keyCode;
}

int CKeyMap::GetKey(ActionKey action)
{
    return keyMap[action];
}

bool CKeyMap::IsActionPressed(BYTE* states, ActionKey action)
{
    int key = keyMap[action];
    return (states[key] & 0x80) != 0;
}

void CKeyMap::LoadDefault()
{
    //SetKey(ActionKey::MoveLeft, DIK_LEFT);
    //SetKey(ActionKey::MoveRight, DIK_RIGHT);
    //SetKey(ActionKey::Jump, DIK_S);
    //SetKey(ActionKey::Jump, DIK_SPACE);
    SetKey(ActionKey::Sit, DIK_DOWN);
    //SetKey(ActionKey::Run, DIK_A);
    //SetKey(ActionKey::Pause, DIK_Q);
    //SetKey(ActionKey::Reload, DIK_R);
    //SetKey(ActionKey::SetDie, DIK_0);
    //SetKey(ActionKey::SetSmall, DIK_1);
    SetKey(ActionKey::SetBig, DIK_2);

    SetKey(ActionKey::MoveLeft, DIK_A);
    SetKey(ActionKey::MoveRight, DIK_D);
    SetKey(ActionKey::Jump, DIK_SPACE);


}

void CKeyMap::SaveToFile(const string& filename)
{
    ofstream out(filename);
    for (auto& pair : keyMap)
    {
        out << (int)pair.first << "=" << pair.second << endl;
    }
    out.close();
}

void CKeyMap::LoadFromFile(const wstring& filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        LoadDefault();
        SaveToFile(WSTRToString(filename)); 
        return;
    }

    int actionInt, key;
    char equal;
    while (in >> actionInt >> equal >> key)
    {
        keyMap[(ActionKey)actionInt] = key; 
    }
    in.close();
}

CKeyMap::~CKeyMap()
{
    this->keyMap.clear();
}

