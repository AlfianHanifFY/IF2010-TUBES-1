#include "Item/Potion/Potion.hpp"

Potion::Potion(const std::string &id, const std::string &name, const char rarity, int baseStat, const vector<Effect *> &effects, int price)
    : Item(id, name, "potion", rarity, baseStat, effects, price) {}
Potion::~Potion() {}

std::string Potion::getType() const
{
    return "Potion";
}

int Potion::getDamage(Unit *target) const
{
    return 0;
}

int Potion::getDefenseBonus() const
{
    return 0;
}
