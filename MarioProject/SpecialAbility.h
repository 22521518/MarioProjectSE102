#pragma once

// Interface for special abilities
class ISpecialAbility
{
public:
    virtual void ActivateAbility() = 0;
    virtual bool HasAbility() const = 0;
    virtual ~ISpecialAbility() {}
};
