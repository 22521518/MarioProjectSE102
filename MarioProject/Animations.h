#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "debug.h"
#include <unordered_map>

using namespace std;

class CAnimation;
typedef CAnimation* LPANIMATION;

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();

	static CAnimations* GetInstance();
};