#ifndef BASICMOB_HPP
#define BASICMOB_HPP

#include <iostream>
using namespace std;

#include "../Mob.hpp"

class BasicMob : public Mob
{
public:
    BasicMob(string name, int level);
    virtual ~BasicMob();

    virtual void act(Unit *target) override;
    string getType() override;
};

#endif
