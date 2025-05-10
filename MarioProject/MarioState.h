#pragma once

class CMario;
typedef CMario* LPMARIO;

class CMarioState
{
protected:
	virtual void OnRun(LPMARIO mario, bool isLeft);
	virtual void OnWalk(LPMARIO mario, bool isLeft);
	virtual void OnJump(LPMARIO mario);
	virtual void OnReleaseJump(LPMARIO mario);
	virtual void OnSit(LPMARIO mario);
	virtual void OnReleaseSit(LPMARIO mario);
	virtual void OnIdle(LPMARIO mario);
	virtual void OnDie(LPMARIO mario);
public:
	CMarioState() {}
	virtual ~CMarioState() {}
	virtual int GetAniId(LPMARIO mario) = 0;

	virtual void GetBoundingBox(LPMARIO mario, float& width, float& height) = 0;
	virtual void HandleStateChange(LPMARIO mario, int state);
};

typedef CMarioState* LPMARIOSTATE;