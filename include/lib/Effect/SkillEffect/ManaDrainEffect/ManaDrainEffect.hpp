#ifndef MANA_DRAIN_EFFECT_HPP
#define MANA_DRAIN_EFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class ManaDrainEffect : public SkillEffect
{
private:
    int manaLossPerTurn;

public:
    ManaDrainEffect(string name, string description, int duration, float effectChance, int manaLossPerTurn);
    virtual ~ManaDrainEffect();

    
    int getManaLossPerTurn() const;

    
    virtual void apply(Unit *target) override;
    virtual void tick(Unit *target) override;
    virtual void remove(Unit *target) override;

    
    ManaDrainEffect(const ManaDrainEffect &other);
    virtual Effect *clone() const override;
};

#endif