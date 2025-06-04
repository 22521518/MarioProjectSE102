#pragma once
#include<map>
#include"Sprite.h"
#include "FontConfig.h"

using namespace std;

class CSpriteFont {
    map<char, LPSPRITE> charMap;
    float width = 8.f;
    float height = 8.f;
    CSpriteFont() {};

    static CSpriteFont* __instance;
public:
    static CSpriteFont* GetInstance();
    void Load();
    void DrawFontText(string text, float x, float y);
    void DrawFontNumber(int number, int digits, float x, float y);
    void DrawFontNumber(int number, int digits, float x, float y, bool zeroBefore);   
};

typedef CSpriteFont* LPSPRITEFONT;