#ifndef HEALTH_DRAIN_EFFECT_HPP
#define HEALTH_DRAIN_EFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class HealthDrainEffect : public SkillEffect
{
private:
    int drainAmount;
    Unit *source;

public:
    HealthDrainEffect(string name, string description, int duration, float effectChance, int drainAmount, Unit *source);
    virtual ~HealthDrainEffect();

    
    int getDrainAmount() const;
    Unit *getSource() const;

    
    void setDrainAmount(int amount);
    void setSource(Unit *source);

    
    virtual void apply(Unit *target) override;
    virtual void tick(Unit *target) override;
    virtual void remove(Unit *target) override;

    
    HealthDrainEffect(const HealthDrainEffect &other);
    virtual Effect *clone() const override;
};

#endif