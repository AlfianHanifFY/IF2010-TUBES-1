#ifndef DECAYEFFECT_HPP
#define DECAYEFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"


class DecayEffect : public SkillEffect
{
private:
    int damage;

public:
    DecayEffect(string name, string description, int duration, float effectChance, int damage);
    virtual ~DecayEffect();
    void apply(Unit *target) override;
    void tick(Unit *target) override;
    void remove(Unit *target) override;

    
    DecayEffect(const DecayEffect &other);
    virtual Effect *clone() const override;
};

#endif