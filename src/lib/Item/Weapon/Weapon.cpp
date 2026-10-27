#include "Item/Weapon/Weapon.hpp"
#include <cstdlib>

Weapon::Weapon(const std::string &id, const std::string &name, const char rarity, int baseStat, const vector<Effect *> &effects, int price)
    : Item(id, name, "weapon", rarity, baseStat, effects, price) {}
Weapon::~Weapon() {}

std::string Weapon::getType() const
{
    return "Weapon";
}

int Weapon::getDamage(Unit *target) const
{
    return getScaledStat(); 
}

int Weapon::getDefenseBonus() const
{
    return 0; 
}
