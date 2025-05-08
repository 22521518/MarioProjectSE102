#pragma once

class CBaseObject {
protected:
    bool isDeleted = false;
    bool isRemovable = false;
    bool isVisible = true;
public:
    CBaseObject() {}

    virtual void Delete() { isDeleted = true; }
    virtual void MakeVisible() { isVisible = true; }
    virtual void MakeInvisible() { isVisible = false; }
    virtual void MakeAlive() { isDeleted = isRemovable ? isDeleted : false; }

    bool IsDeleted() const { return isDeleted; }
    bool IsRemovable() const { return isRemovable; }
    bool IsVisible() const { return isVisible; }

    static bool IsDeleted(const CBaseObject* object) { return object->IsDeleted() && object->IsRemovable(); }
};

typedef CBaseObject* LPBASEOBJECT;
