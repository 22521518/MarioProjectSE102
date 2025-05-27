#pragma once

class CMario;
typedef CMario* LPMARIO;

class CMarioState
{
protected:
	LPMARIO mario = nullptr;

	virtual void OnRun(bool isLeft);
	virtual void OnWalk(bool isLeft);
	virtual void OnJump();
	virtual void OnReleaseJump();
	virtual void OnSit();
	virtual void OnReleaseSit();
	virtual void OnIdle();
	virtual void OnDie();
public:
	CMarioState(LPMARIO mario) { this->mario = mario; }
	virtual ~CMarioState() {}
	virtual int GetAniId() = 0;

	virtual void GetBoundingBox(float& width, float& height) = 0;
	virtual void HandleStateChange(int state);
};

typedef CMarioState* LPMARIOSTATE;