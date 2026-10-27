#ifndef HEAL_EFFECT_HPP
#define HEAL_EFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class HealEffect : public SkillEffect
{
private:
    int baseHealValue;
    int totalHealAmount;

public:
    HealEffect(string name, string description, int duration, float effectChance, int baseHealValue);
    virtual ~HealEffect();

    
    int getBaseHealValue() const;
    int getTotalHealAmount() const;

    
    void setTotalHealAmount(int amount);

    
    virtual void apply(Unit *target) override;
    virtual void remove(Unit *target) override;

    
    HealEffect(const HealEffect &other);
    virtual Effect *clone() const override;
};

#endif