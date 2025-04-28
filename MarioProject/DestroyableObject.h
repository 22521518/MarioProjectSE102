#pragma once

class CDestroyableObject {
public:
	virtual void OnDestroy() = 0;
};

typedef CDestroyableObject* LPDESTROYABLEOBJECT;