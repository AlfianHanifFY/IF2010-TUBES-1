#ifndef WEAKENEFFECT_HPP
#define WEAKENEFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class WeakenEffect : public SkillEffect
{
private:
    int attackDamageReduction;

public:
    WeakenEffect(string name, string description, int duration, float effectChance, int attackDamageReduction);
    virtual ~WeakenEffect();
    void apply(Unit *target) override;
    void remove(Unit *target) override;

    
    WeakenEffect(const WeakenEffect &other);
    virtual Effect *clone() const override;
};

#endif