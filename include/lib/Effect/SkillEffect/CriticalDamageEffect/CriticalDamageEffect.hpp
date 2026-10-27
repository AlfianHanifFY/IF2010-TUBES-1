#ifndef CRITICAL_DAMAGE_EFFECT_HPP
#define CRITICAL_DAMAGE_EFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class CriticalDamageEffect : public SkillEffect
{
private:
    float damageMultiplier;
    int baseAttackDamage;

public:
    CriticalDamageEffect(string name, string description, int duration, float effectChance, float damageMultiplier);
    virtual ~CriticalDamageEffect();

    
    float getDamageMultiplier() const;

    
    virtual void apply(Unit *target) override;
    
    virtual void remove(Unit *target) override;

    
    CriticalDamageEffect(const CriticalDamageEffect &other);
    virtual Effect *clone() const override;
};

#endif