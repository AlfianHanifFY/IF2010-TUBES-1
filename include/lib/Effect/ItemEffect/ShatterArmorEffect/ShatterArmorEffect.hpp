#ifndef SHATTERARMOREFFECT_HPP
#define SHATTERARMOREFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"


class ShatterArmorEffect : public ItemEffect
{
public:
    ShatterArmorEffect();
    ~ShatterArmorEffect();
    
    void apply(Unit *target) override;
    void remove(Unit *target) override;
    void tick(Unit *target) override;

    virtual Effect *clone() const override;
    ShatterArmorEffect(const ShatterArmorEffect &other);
};
#endif