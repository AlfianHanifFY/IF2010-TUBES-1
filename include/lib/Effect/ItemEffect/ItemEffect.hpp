#ifndef ITEMEFFECT_HPP
#define ITEMEFFECT_HPP

#include <iostream>
using namespace std;

#include "../Effect.hpp"

class ItemEffect : public Effect
{
public:
    ItemEffect(const string &name, const string &description, int duration, float effectChance);
    virtual ~ItemEffect();
    virtual void apply(Unit *target) override = 0;
    virtual void remove(Unit *target) override = 0;
    virtual Effect *clone() const override = 0;
    ItemEffect(const ItemEffect &other);
};

#endif