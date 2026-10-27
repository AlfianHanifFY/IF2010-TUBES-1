#include "Item/Pendant/Pendant.hpp"

Pendant::Pendant(const std::string &id, const std::string &name, const char rarity, int baseStat, const vector<Effect *> &effects, int price)
    : Item(id, name, "pendant", rarity, baseStat, effects, price) {}
Pendant::~Pendant() {}

std::string Pendant::getType() const
{
    return "Pendant";
}

void Pendant::applyPassive(Unit *target) const
{
    int bonus = getScaledStat();
    int currentAgility = target->getStat(2);
    target->setStat(0, currentAgility + bonus);
    target->setStat(1, currentAgility + bonus);
    target->setStat(2, currentAgility + bonus);
}

void Pendant::removePassive(Unit *target) const
{
    int bonus = getScaledStat();
    int currentAgility = target->getStat(2);
    target->setStat(0, currentAgility - bonus);
    target->setStat(1, currentAgility - bonus);
    target->setStat(2, currentAgility - bonus);
}

int Pendant::getDamage(Unit *target) const
{
    return 0;
}

int Pendant::getDefenseBonus() const
{
    return 0;
}
