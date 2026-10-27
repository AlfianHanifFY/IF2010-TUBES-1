#include "Item/Item.hpp"

Item::Item(const std::string &id, const std::string &name, const std::string &type, const char rarity, int baseStat, const vector<Effect *> &effects, int price) : id(id), name(name), type(type), rarity(rarity), baseStat(baseStat), effects(effects), price(price) {}
Item::~Item() {}

std::string Item::getID() const
{
    return this->id;
}
std::string Item::getName() const
{
    return this->name;
}
char Item::getRarity() const
{
    return this->rarity;
}
int Item::getBaseStat() const
{
    return this->baseStat;
}
vector<Effect *> Item::getEffects() const
{
    return this->effects;
}
int Item::getPrice() const
{
    return price;
}

void Item::setID(string id)
{
    this->id = id;
}
void Item::setName(string name)
{
    this->name = name;
}
void Item::setType(string type)
{
    this->type = type;
}
void Item::setRarity(char rarity)
{
    this->rarity = rarity;
}
void Item::setBaseStat(int baseStat)
{
    this->baseStat = baseStat;
}
void Item::setPrice(int price)
{
    this->price = price;
}

void Item::addEffect(Effect *effect)
{
    Rarity r(this->rarity);
    if (effects.size() < r.getMaxEffectCount())
    {
        effects.push_back(effect);
    }
    else
    {
        std::cout << "Item dengan rarity " << r.getRarityName()
                  << " tidak bisa menambahkan lebih dari "
                  << r.getMaxEffectCount() << " efek.\n";
    }
}

int Item::getScaledStat() const
{
    Rarity r(this->rarity);
    return static_cast<int>(baseStat * r.getMultiplier());
}

void Item::scaleStat(Unit *target) const
{
    Rarity r(this->rarity);
    float scaled = r.getMultiplier() * this->baseStat;
    for (int i = 0; i < 3; ++i)
    {
        int stat = target->getStat(i) + static_cast<int>(scaled);
        target->setStat(i, stat);
    }
}

void Item::removeScale(Unit *target) const
{
    Rarity r(this->rarity);
    float scaled = r.getMultiplier() * this->baseStat;
    for (int i = 0; i < 3; ++i)
    {
        int stat = target->getStat(i) - static_cast<int>(scaled);
        target->setStat(i, stat);
    }
}
int Item::getBuyPrice() const
{
    int factor = 1;
    switch (rarity)
    {
    case 'F':
        factor = 1;
        break; 
    case 'E':
        factor = 2;
        break; 
    case 'D':
        factor = 5;
        break; 
    case 'C':
        factor = 10;
        break; 
    case 'B':
        factor = 20;
        break; 
    case 'A':
        factor = 50;
        break; 
    case 'S':
        factor = 50;
        break;
    default:
        factor = 1;
        break; 
    }
    return price * factor;
}

int Item::getSellPrice() const
{
    return static_cast<int>(getBuyPrice() * 0.7);
}

void Item::use(Unit *target)
{
    for (int i = 0; i < effects.size(); i++)
    {
        target->addEffect(effects[i]->clone());
    }
}