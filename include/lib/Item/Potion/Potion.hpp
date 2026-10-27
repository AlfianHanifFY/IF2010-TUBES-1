#ifndef POTION_HPP
#define POTION_HPP

#include <iostream>
using namespace std;

#include "../Item.hpp"

class Potion : public Item
{
private:
    std::string type;

public:
    Potion(const std::string &id, const std::string &name, const char rarity, int baseStat, const vector<Effect *> &effects, int price);
    virtual ~Potion();
    
    std::string getType() const override;
    
    int getDamage(Unit *target) const;
    int getDefenseBonus() const;
};

#endif
