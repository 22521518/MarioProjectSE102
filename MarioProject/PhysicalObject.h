#pragma once
#include <Windows.h>
#include <vector>
#include <D3DX10.h>

#include "DirectionType.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

using namespace std;
constexpr int ID_TEX_BBOX = -100;		// special texture to draw object bounding box
constexpr float BBOX_ALPHA = 0.25f;		// Bounding box transparency

class CPhysicalObject : public CGameObject {
protected:
	float originVX, originVY, originAX, originAY;
	DirectionXAxisType originNX;
	float vx, vy;
	float ax, ay;
	DirectionXAxisType nx = DirectionXAxisType::Left;

public:
	CPhysicalObject(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left)
		:CGameObject(x, y), vx(vx), vy(vy), ax(ax), ay(ay), nx(nx), 
		originVX(vx), originVY(vy), originAX(ax), originAY(ay), originNX(nx) {};

	// game object method
	virtual void Render() = 0;

	// physical object method
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) = 0;
	virtual int IsCollidable() = 0;
	virtual int IsBlocking() = 0;
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) = 0;


	DirectionXAxisType GetNX() const { return this->nx; }
	void SetAcceleration(float ax, float ay) { this->ax = ax, this->ay = ay; }
	void GetAcceleration(float& ax, float& ay) const { ax = this->ax; ay = this->ay; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) const { vx = this->vx; vy = this->vy; }

	void SetOriginAcceleration(float ax, float ay) { this->originAX = ax, this->originAY = ay; }
	void GetOriginAcceleration(float& ax, float& ay) const { ax = this->originAX; ay = this->originAY; }
	void SetOriginSpeed(float vx, float vy) { this->originVX = vx, this->originVY = vy; }
	void GetOriginSpeed(float& vx, float& vy) const { vx = this->originVX; vy = this->originVY; }

	void ResetState() override
	{ 
		CGameObject::ResetState();
		this->vx = originVX;
		this->vy = originVY;
		this->ax = originAX;
		this->ay = originAY;
		this->nx = originNX;
	};
};
typedef CPhysicalObject* LPPHYSICALOBJECT;