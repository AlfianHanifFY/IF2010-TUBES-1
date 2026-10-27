#ifndef RAGE_EFFECT_HPP
#define RAGE_EFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class RageEffect : public SkillEffect
{
private:
    float statMultiplier;
    int originalStrength;
    int originalIntelligence;
    int originalAgility;

public:
    RageEffect(string name, string description, int duration, float effectChance, float statMultiplier);
    virtual ~RageEffect();

    
    float getStatMultiplier() const;

    
    virtual void apply(Unit *target) override;
    virtual void tick(Unit *target) override;
    virtual void remove(Unit *target) override;

    
    RageEffect(const RageEffect &other);
    virtual Effect *clone() const override;
};

#endif