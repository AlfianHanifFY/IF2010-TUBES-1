#ifndef MAGE_HPP
#define MAGE_HPP

#include <iostream>
using namespace std;

#include "../Character.hpp"

class Mage : public Character
{
private:
    int extraMana;

public:
    Mage(string name);
    virtual ~Mage();

    
    int getExtraMana() const;
    void setExtraMana(int extraMana);
    virtual string getCharType() const override;

    int attack(Unit *target) override;
    bool useSkill(Skill *skill, Unit *target) override;
    void levelUp() override;

    void initPath() override;
};

#endif
