#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>
#include "../Unit/Unit.hpp"
#include <vector>
#include "../Rarity/Rarity.hpp"
#include "../Effect/Effect.hpp"

using namespace std;

class Item
{
protected:
    std::string id;
    std::string name;
    std::string type;
    char rarity;
    int baseStat;
    vector<Effect *> effects;
    int price;

public:
    Item(const std::string &id, const std::string &name, const std::string &type, const char rarity, int baseStat, const vector<Effect *> &effects, int price);
    virtual ~Item();

    
    std::string getID() const;
    std::string getName() const;
    virtual std::string getType() const = 0;
    char getRarity() const;
    int getBaseStat() const;
    vector<Effect *> getEffects() const;
    int getPrice() const;

    
    void setID(string id);
    void setName(string name);
    void setType(string type);
    void setRarity(char rarity);
    void setBaseStat(int baseStat);
    void setPrice(int price);

    
    int getScaledStat() const;
    void scaleStat(Unit *target) const;
    void removeScale(Unit *target) const;
    void addEffect(Effect *effect);
    int getBuyPrice() const;
    int getSellPrice() const;
    void use(Unit *target);
};

#endif
