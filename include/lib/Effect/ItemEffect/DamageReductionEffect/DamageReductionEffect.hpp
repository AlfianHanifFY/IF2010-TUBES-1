#ifndef DAMAGEREDUCTIONEFFECT_HPP
#define DAMAGEREDUCTIONEFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"


class DamageReductionEffect : public ItemEffect
{
private:
    int baseDefense;
public:
    DamageReductionEffect();
    ~DamageReductionEffect();
    
    void apply(Unit *target) override;
    void remove(Unit *target) override;
    int getReductionPercent() const; 

    virtual Effect *clone() const override;
    DamageReductionEffect(const DamageReductionEffect &other);
};
#endif