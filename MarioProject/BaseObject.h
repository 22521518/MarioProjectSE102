#pragma once

class CBaseObject {
protected:
    bool isDeleted;
    bool isRemovable = false;
public:
    CBaseObject() { this->isDeleted = false; }

    virtual void Delete() { isDeleted = true; }
    virtual void MakeAlive() { isDeleted = false; }
    bool IsDeleted() const { return isDeleted; }
    bool IsRemovable() const { return isRemovable; }

    static bool IsDeleted(const CBaseObject* object) { return object->IsDeleted() && object->IsRemovable(); }
};

typedef CBaseObject* LPBASEOBJECT;
