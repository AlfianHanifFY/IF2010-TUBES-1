#ifndef ARMOR_HPP
#define ARMOR_HPP

#include <iostream>
using namespace std;

#include "../Item.hpp"

class Armor : public Item
{
private:
    std::string type;
    string part;

public:
    Armor(const std::string &id, const std::string &name, const char rarity, int baseStat, const vector<Effect *> &effects, int price, const std::string &part);
    virtual ~Armor();
    
    std::string getType() const override;
    
    int getDamage(Unit *target) const;
    int getDefenseBonus() const;
    string getPart() const;
};

#endif
