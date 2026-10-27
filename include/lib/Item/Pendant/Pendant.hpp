#ifndef PENDANT_HPP
#define PENDANT_HPP

#include <iostream>
using namespace std;

#include "../Item.hpp"

class Pendant : public Item
{
private:
    std::string type;

public:
    Pendant(const std::string &id, const std::string &name, const char rarity, int baseStat, const vector<Effect *> &effects, int price);
    virtual ~Pendant();
    
    std::string getType() const override;
    
    int getDamage(Unit *target) const;
    int getDefenseBonus() const;
    void applyPassive(Unit *target) const;
    void removePassive(Unit *target) const;
};

#endif
