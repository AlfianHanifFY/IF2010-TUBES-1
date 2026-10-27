#ifndef ASSASIN_HPP
#define ASSASIN_HPP

#include <iostream>
using namespace std;

#include "../Character.hpp"

class Assasin : public Character
{
private:
    float criticalChance;
    float criticalMultiplier;

public:
    Assasin(string name);
    virtual ~Assasin();

    

    
    float getCriticalChance() const;
    float getCriticalMultiplier() const;
    void setCriticalChance(float criticalChance);
    void setCriticalMultiplier(float criticalMultiplier);
    string getCharType() const override;

    int attack(Unit *target) override;
    int takeDamage(int damage) override;
    void levelUp() override;

    void initPath() override;
};

#endif
