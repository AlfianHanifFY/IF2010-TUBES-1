#ifndef MANAREGENEFFECT_HPP
#define MANAREGENEFFECT_HPP

#include <string>
#include <iostream>
using namespace std;

#include "../ItemEffect.hpp"
#include "../../../Unit/Unit.hpp"


class ManaRegenEffect : public ItemEffect
{
public:
    ManaRegenEffect();
    ~ManaRegenEffect();
    
    void apply(Unit *target) override;
    void tick(Unit *target) override;
    void remove(Unit *target) override;

    virtual Effect *clone() const override;
    ManaRegenEffect(const ManaRegenEffect &other);
};

#endif