#pragma once
#include <vector>
#include <string>
#include <cstddef>
#include <unordered_map>

#include "BaseObject.h"
#include "debug.h"

using namespace std;

class CGameObject : public CBaseObject {
	float originX;
	float originY;

protected:
	float x;
	float y;

public:
	CGameObject(float x = 0, float y = 0) : CBaseObject(), x(x), y(y), originX(x), originY(y) {}
	static CGameObject* CreateGameObject(int object_type, float x, float y, unordered_map<string, float> additionalFieldInfo, LPGAMEOBJECT player);

	virtual void Render() = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void GetBoundingBox(RECT& rect);
	virtual void RenderBoundingBox();

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) const { x = this->x; y = this->y; }
	void GetOriginalPosition(float& x, float& y) const { x = this->originX; y = this->originY; }
	void SetOriginalPosition(float x, float y) { this->originX = x, this->originY = y; }


	virtual void ResetState() { this->x = originX, this->y = originY; };
};

typedef CGameObject* LPGAMEOBJECT;