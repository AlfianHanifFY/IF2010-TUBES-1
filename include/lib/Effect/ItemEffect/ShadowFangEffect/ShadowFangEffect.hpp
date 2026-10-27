#ifndef SHADOWFANGEFFECT_HPP
#define SHADOWFANGEFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"




class ShadowFangEffect : public ItemEffect
{
private:
    int originalAttackDamage = -1;

public:
    ShadowFangEffect();
    ~ShadowFangEffect();
    
    void apply(Unit *target) override;
    void tick(Unit *target) override;
    void remove(Unit *target) override;

    virtual Effect *clone() const override;
    ShadowFangEffect(const ShadowFangEffect &other);
};

#endif
