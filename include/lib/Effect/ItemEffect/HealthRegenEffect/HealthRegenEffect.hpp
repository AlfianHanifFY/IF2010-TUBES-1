#ifndef HEALTHREGENEFFECT_HPP
#define HEALTHREGENEFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"


class HealthRegenEffect : public ItemEffect
{
public:
    HealthRegenEffect();
    ~HealthRegenEffect();
    
    void apply(Unit *target) override;
    void remove(Unit *target) override;
    void tick(Unit *target) override;

    virtual Effect *clone() const override;
    HealthRegenEffect(const HealthRegenEffect &other);
};
#endif