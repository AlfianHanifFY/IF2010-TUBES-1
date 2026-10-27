#ifndef STUNEFFECT_HPP
#define STUNEFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class StunEffect : public SkillEffect
{
public:
    StunEffect(string name, string description, int duration, float effectChance);
    virtual ~StunEffect();
    void apply(Unit *target) override;
    void remove(Unit *target) override;

    
    StunEffect(const StunEffect &other);
    virtual Effect *clone() const override;
};

#endif