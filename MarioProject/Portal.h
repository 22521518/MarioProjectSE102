#pragma once
#include "StaticObject.h"
#include "CollidableWithMario.h"

class CPortal :
	public CStaticObject, public CCollidableWithMario
{
protected:
	int scene_id;	// target scene to switch to 
	int animation_id = 0; // animation when mario jump in
	float animation_width = 0, animation_height = 0;

	ULONGLONG time_start = 0;
	
	// animation
	int isPipePort; // > 0 down, < 0 up

	// from bonus
	bool isReturnToExisting;
	int px, py;

	float width;
	float height;
public:	
	CPortal(float l, float t, float r, float b, int scene_id, int isPipe = false, bool isReturnToExist = false, int px = 0, int py = 0);

	static unordered_map<string, float> GetAdditionalFieldInfo(vector<string> tokens);
	bool TimeToMove() const;

	// game object method
	void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;
	void Render() override;

	// physical object method
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual void RenderBoundingBox() override;

	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;

	// portal method
	int GetSceneId() const { return scene_id; }
};

typedef CPortal* LPPORTAL;