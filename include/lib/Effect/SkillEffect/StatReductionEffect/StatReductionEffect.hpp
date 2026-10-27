#ifndef STAT_REDUCTION_EFFECT_HPP
#define STAT_REDUCTION_EFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class StatReductionEffect : public SkillEffect
{
private:
    float attackReductionMultiplier;
    float defenseReductionMultiplier;
    int baseAttack;
    int baseDefense;

public:
    StatReductionEffect(string name, string description, int duration, float effectChance, float attackReductionMultiplier, float defenseReductionMultiplier);
    virtual ~StatReductionEffect();

    
    float getAttackReductionMultiplier() const;
    float getDefenseReductionMultiplier() const;

    
    virtual void apply(Unit *target) override;
    virtual void tick(Unit *target) override;
    virtual void remove(Unit *target) override;

    
    StatReductionEffect(const StatReductionEffect &other);
    virtual Effect *clone() const override;
};

#endif