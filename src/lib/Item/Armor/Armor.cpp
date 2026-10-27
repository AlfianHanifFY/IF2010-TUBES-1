#include "Item/Armor/Armor.hpp"

Armor::Armor(const std::string &id, const std::string &name, const char rarity, int baseStat, const vector<Effect *> &effects, int price, const std::string &part)
    : Item(id, name, "armor", rarity, baseStat, effects, price)
{
    this->part = part;
}

Armor::~Armor() {}

std::string Armor::getType() const
{
    return "Armor";
}

int Armor::getDefenseBonus() const
{
    return getScaledStat(); 
}

int Armor::getDamage(Unit *target) const
{
    return 0; 
}

std::string Armor::getPart() const
{
    return this->part;
}