#pragma once

class CMario;
typedef CMario* LPMARIO;

class CMarioState
{
	void OnRun(LPMARIO mario, bool isLeft);
	void OnWalk(LPMARIO mario, bool isLeft);
	void OnJump(LPMARIO mario);
	void OnReleaseJump(LPMARIO mario);
	void OnSit(LPMARIO mario);
	void OnReleaseSit(LPMARIO mario);
	void OnIdle(LPMARIO mario);
	void OnDie(LPMARIO mario);
public:
	virtual ~CMarioState() {}
	virtual int GetAniId(LPMARIO mario) = 0;

	virtual void GetBoundingBox(LPMARIO mario, float& width, float& height) = 0;
	virtual void HandleStateChange(LPMARIO mario, int state);
};

typedef CMarioState* LPMARIOSTATE;