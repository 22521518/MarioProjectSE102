#pragma once

struct CCoordination {
	float left;
	float top;
	float right;
	float bottom;

	CCoordination() {
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	CCoordination(int l, int t, int r, int b) {
		left = l * 1.0f;
		top = t * 1.0f;
		right = r * 1.0f;
		bottom = b * 1.0f;
	}


	CCoordination(float l, float t, float r, float b) {
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
};

typedef CCoordination* LPCOORDINATION;