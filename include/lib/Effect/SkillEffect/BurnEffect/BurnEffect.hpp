#ifndef BURNEFFECT_HPP
#define BURNEFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class BurnEffect : public SkillEffect
{
private:
    int damagePerTurn;

public:
    BurnEffect(string name, string description, int duration, float effectChance, int damagePerTurn);
    virtual ~BurnEffect();
    void apply(Unit *target) override;
    void tick(Unit *target) override;
    void remove(Unit *target) override;

    
    int getDamagePerTurn() const;

    
    BurnEffect(const BurnEffect &other);

    virtual Effect *clone() const override;
};

#endif