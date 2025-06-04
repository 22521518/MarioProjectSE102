#pragma once
#include "HUDObject.h"
#include "vector"

using namespace std;

class CHUDContainer : public CHUDObject {
protected:
		vector<LPHUDOBJECT> items;
public:
	CHUDContainer() {}
};

