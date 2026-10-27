#ifndef CRIMSONCURSEEFFECT_HPP
#define CRIMSONCURSEEFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"


class CrimsonCurseEffect : public ItemEffect
{
public:
    CrimsonCurseEffect();
    ~CrimsonCurseEffect();
    
    void apply(Unit *target) override;
    void tick(Unit *target) override;
    void remove(Unit *target) override;

    
    CrimsonCurseEffect(const CrimsonCurseEffect &other);
    virtual Effect *clone() const override;
};

#endif