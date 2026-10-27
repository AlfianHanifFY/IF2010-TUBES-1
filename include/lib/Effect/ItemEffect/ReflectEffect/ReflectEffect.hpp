#ifndef REFLECTEFFECT_HPP
#define REFLECTEFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"


class ReflectEffect : public ItemEffect
{
private:
    float reflectPercentage;
public:
    ReflectEffect();
    ~ReflectEffect();

    
    void apply(Unit *target) override;
    void tick(Unit *target) override;
    void remove(Unit *target) override;
    virtual Effect *clone() const override;
    ReflectEffect(const ReflectEffect &other);
};
#endif