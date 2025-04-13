#pragma once
#include <Windows.h>
#include <vector>
#include <D3DX10.h>

#include "DirectionType.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define BBOX_ALPHA 0.25f		// Bounding box transparency

class CPhysicalObject; typedef CPhysicalObject* LPPHYSICALOBJECT;

class CPhysicalObject : public CGameObject {

protected:
	float vx = 0.0f, vy = 0.0f;
	float ax = 0.0f, ay = 0.0f;
	DirectionXAxisType nx = DirectionXAxisType::Left;

public:
	CPhysicalObject(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left)
		:CGameObject(x, y), vx(vx), vy(vy), ax(ax), ay(ay), nx(nx) {
	};

	// game object method
	virtual void Render() = 0;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) = 0;
	virtual int IsCollidable() = 0;
	virtual int IsBlocking() = 0;
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) = 0;

	virtual void onHit() {};
	virtual void RenderBoundingBox();
	virtual void GetBoundingBox(RECT& rect);

	void SetAcceleration(float ax, float ay) { this->ax = ax, this->ay = ay; }
	void GetAcceleration(float& ax, float& ay) const { ax = this->ax; ay = this->ay; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) const { vx = this->vx; vy = this->vy; }
};
