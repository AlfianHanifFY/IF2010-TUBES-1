#ifndef BERSERKER_HPP
#define BERSERKER_HPP

#include <iostream>
using namespace std;

#include "../Character.hpp"

class Berserker : public Character
{
private:
    float rageMultiplier;

public:
    Berserker(string name);
    virtual ~Berserker();

    
    float getRageMultiplier() const;
    void setRageMultiplier(float rageMultiplier);
    string getCharType() const override;

    int attack(Unit *target) override;
    bool useSkill(Skill *skill, Unit *target) override;
    void levelUp() override;
    void reset() override;

    void initPath() override;
};

#endif
