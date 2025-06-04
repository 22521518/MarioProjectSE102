#pragma once
#include "HUDObject.h"

class CHUDScoreboard : public CHUDObject {

private:
	int backgroundId = 0;

	ULONGLONG* time_remain;
	ULONGLONG* scores;
	ULONGLONG* lives;
	ULONGLONG* coins;
protected:
	vector<LPHUDOBJECT> items;

public:
	CHUDScoreboard(ULONGLONG* time, ULONGLONG* score, ULONGLONG* life, ULONGLONG* coin);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {};
	void Render() override;

	~CHUDScoreboard() { items.clear(); }
};