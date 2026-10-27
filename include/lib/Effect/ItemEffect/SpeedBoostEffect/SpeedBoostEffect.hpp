#ifndef SPEEDBOOSTEFFECT_HPP
#define SPEEDBOOSTEFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"


class SpeedBoostEffect : public ItemEffect
{
public:
    SpeedBoostEffect();
    ~SpeedBoostEffect();
    
    void apply(Unit *target) override;
    void tick(Unit *target) override;
    void remove(Unit *target) override;

    virtual Effect *clone() const override;
    SpeedBoostEffect(const SpeedBoostEffect &other);
};
#endif