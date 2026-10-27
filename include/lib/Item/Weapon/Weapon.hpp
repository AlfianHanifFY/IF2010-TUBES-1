#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
using namespace std;

#include "../Item.hpp"
#include "../../Effect/Effect.hpp"

class Weapon : public Item
{
public:
    Weapon(const std::string &id, const std::string &name, const char rarity, int baseStat, const vector<Effect *> &effects, int price);
    virtual ~Weapon();

    
    std::string getType() const override;

    
    int getDamage(Unit *target) const;
    int getDefenseBonus() const;
};

#endif
