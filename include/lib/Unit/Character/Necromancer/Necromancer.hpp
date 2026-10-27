#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include <iostream>
using namespace std;

#include "../Character.hpp"

class Necromancer : public Character
{
private:
    float summonChance;
    int summonDamage;

public:
    Necromancer(string name);
    virtual ~Necromancer();
    int summon;
    
    int getSummon() const;
    float getSummonChance() const;
    int getSummonDamage() const;
    void setSummonChance(float summonChance);
    void setSummonDamage(int summonDamage);
    string getCharType() const override;

    int attack(Unit *target) override;
    bool useSkill(Skill *skill, Unit *target) override;
    void levelUp() override;
    void reset() override;

    void initPath() override;
};

template <typename T>
int getCountSummonFrom(Unit *unit)
{
    if (T *derived = dynamic_cast<T *>(unit))
    {
        return derived->summon;
    }
    return 0;
}

#endif
