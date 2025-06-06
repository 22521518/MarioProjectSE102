#pragma once
#include "StaticObject.h"
#include "CollidableWithMario.h"

class CPortal :
	public CStaticObject, public CCollidableWithMario
{
protected:
	int scene_id;	// target scene to switch to 
	
	// animation
	bool isPipePort;

	// from bonus
	bool isReturnToExisting;
	int px, py;

	float width;
	float height;
public:	
	CPortal(float l, float t, float r, float b, int scene_id, bool isPipe = false, bool isReturnToExist = false, int px = 0, int py = 0);

	static unordered_map<string, float> GetAdditionalFieldInfo(vector<string> tokens);

	// game object method
	virtual void Render();

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