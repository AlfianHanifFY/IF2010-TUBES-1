#ifndef DULLINGCURSEEFFECT_HPP
#define DULLINGCURSEEFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"


class DullingCurseEffect : public ItemEffect
{
public:
    DullingCurseEffect();
    ~DullingCurseEffect();
    
    void apply(Unit *target) override;
    void remove(Unit *target) override;
    void tick(Unit *target) override;

    virtual Effect *clone() const override;
    DullingCurseEffect(const DullingCurseEffect &other);
};
#endif