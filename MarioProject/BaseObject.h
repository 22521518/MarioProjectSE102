#pragma once

class CBaseObject {
protected:
    bool isDeleted;

public:
    CBaseObject() { this->isDeleted = false; }

    virtual void Delete() { isDeleted = true; }
    bool IsDeleted() const { return isDeleted; }

    static bool IsDeleted(const CBaseObject* object) { return object->IsDeleted(); }
};

typedef CBaseObject* LPBASEOBJECT;
