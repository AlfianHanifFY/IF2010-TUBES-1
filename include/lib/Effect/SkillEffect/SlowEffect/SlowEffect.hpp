#ifndef SLOWEFFECT_HPP
#define SLOWEFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class SlowEffect : public SkillEffect
{
private:
    int baseAgility;
    float agilityMultiplier;

public:
    SlowEffect(string name, string description, int duration, float effectChance, float agilityMultiplier);
    virtual ~SlowEffect();
    void apply(Unit *target) override;
    void remove(Unit *target) override;

    
    SlowEffect(const SlowEffect &other);
    virtual Effect *clone() const override;
};

#endif