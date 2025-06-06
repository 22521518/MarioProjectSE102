#include "SpriteFont.h"
#include "FontConfig.h"
#include "FontSpriteIDs.h"

CSpriteFont* CSpriteFont::__instance = nullptr;
CSpriteFont* CSpriteFont::GetInstance()
{
    if (__instance == nullptr) {
        __instance = new CSpriteFont();
    }
    return __instance;
}

void CSpriteFont::Load()
{
    charMap['0'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_0);
    charMap['1'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_1);
    charMap['2'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_2);
    charMap['3'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_3);
    charMap['4'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_4);
    charMap['5'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_5);
    charMap['6'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_6);
    charMap['7'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_7);
    charMap['8'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_8);
    charMap['9'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_9);

    charMap['A'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_A);
    charMap['B'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_B);
    charMap['C'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_C);
    charMap['D'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_D);
    charMap['E'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_E);
    charMap['F'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_F);
    charMap['G'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_G);
    charMap['H'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_H);
    charMap['I'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_I);
    charMap['J'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_J);
    charMap['K'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_K);
    charMap['L'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_L);
    charMap['M'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_M);
    charMap['N'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_N);
    charMap['O'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_O);
    charMap['P'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_P);
    charMap['Q'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_Q);
    charMap['R'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_R);
    charMap['S'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_S);
    charMap['T'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_T);
    charMap['U'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_U);
    charMap['V'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_V);
    charMap['W'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_W);
    charMap['S'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_S);
    charMap['Y'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_Y);
    charMap['Z'] = CSprites::GetInstance()->Get(ID_SPRITE_CHAR_Z);
}

void CSpriteFont::DrawFontText(string text, float x, float y)
{
    for (char c : text) {
        if (charMap.find(c) != charMap.end()) {
            charMap[c]->Draw(x, y);
            x += CHAR_WIDTH;
        }
    }
}

void CSpriteFont::DrawFontNumber(int number, int digits, float x, float y) { 
        string numStr = to_string(number);
        if (numStr.length() < digits) {
            numStr.insert(0, digits - numStr.length(), '0');
        }

        for (char c : numStr) {
            if (charMap.find(c) != charMap.end()) {
                charMap[c]->Draw(x - width / 2, y - height / 2);
            }
            x += CHAR_WIDTH;
        }
 };

void CSpriteFont::DrawFontNumber(int number, int digits, float x, float y, bool zeroBefore)
{
    string numStr = to_string(number);
    if (zeroBefore && numStr.length() < digits) {
        numStr.insert(0, digits - numStr.length(), '0');
    }
    DebugOut(L"[DIMIO] %d, size: %d, >>> %d\n", zeroBefore, numStr.length(), digits - numStr.length());

    for (char c : numStr) {
        if (charMap.find(c) != charMap.end()) {
            charMap[c]->Draw(x - width / 2, y - height / 2);
        }
        x += CHAR_WIDTH;
    }
}
