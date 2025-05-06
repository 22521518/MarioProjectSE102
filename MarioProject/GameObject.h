#pragma once
#include <vector>
#include <string>
#include <cstddef>
#include <unordered_map>

#include "BaseObject.h"
#include "debug.h"

using namespace std;

class CGameObject : public CBaseObject {
protected:
	float x;
	float y;

public:
	CGameObject(float x = 0, float y = 0) : CBaseObject(), x(x), y(y) {}
	static CGameObject* CreateGameObject(int object_type, float x, float y, unordered_map<string, float> additionalFieldInfo, LPGAMEOBJECT player);

	virtual void Render() = 0;

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) const { x = this->x; y = this->y; }
};

typedef CGameObject* LPGAMEOBJECT;