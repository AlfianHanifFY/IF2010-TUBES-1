#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <map>
using namespace std;

#include "../Unit.hpp"
#include "../../Inventory/Inventory.hpp"
#include "../../SkillTree/SkillTree.hpp"
#include "../../Item/Item.hpp"
#include "../../Item/Weapon/Weapon.hpp"

class Character : public Unit
{
protected:
    int exp;
    int mastery;
    int gold;
    Inventory *inventory;
    SkillTree *skillPath;

    
    Item *armors[3];
    Item *pendant = nullptr;
    Item *weapon = nullptr;

public:
    Character(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int level, int exp, int mastery, int gold);
    virtual ~Character();

    
    int getLevel() const;
    int getExp() const;
    int getMastery() const;
    int getGold() const;
    Inventory &getInventory() const;
    string getRank();

    void setExp(int exp);
    void setMastery(int mastery);
    void setGold(int gold);

    
    virtual int attack(Unit *target);
    virtual void levelUp() = 0;
    virtual void addExp(int amount);
    virtual void addMastery(int amount);
    virtual void addGold(int amount);
    virtual bool learnSkill(Skill *skill);

    virtual string getCharType() const = 0;

    
    
    

    
    Item *getHead();
    Item *getBody();
    Item *getFoot();
    Item *getWeapon();
    Item *getPendant();
    void printEquipped() const;
    bool equipItem(Item *item);
    bool unequipItem(Item *item);

    void useGold(int gold);

    SkillTree *getSkillTree();

    virtual void initPath() = 0;

    void applyItemEffect();
};

#endif
