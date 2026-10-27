#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include <iostream>
using namespace std;

#include "../Character.hpp"

class Fighter : public Character
{
private:
    float blockChance;

public:
    Fighter(string name);
    ~Fighter();

    
    float getBlockChance() const;
    void setBlockChance(float blockChance);
    string getCharType() const override;

    int takeDamage(int damage) override;
    bool useSkill(Skill *skill, Unit *target) override;
    void levelUp() override;

    void initPath() override;
};

#endif
