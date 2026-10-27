#ifndef BOSSMOB_HPP
#define BOSSMOB_HPP

#include <iostream>
using namespace std;

#include "../Mob.hpp"

class BossMob : public Mob
{
protected:
    bool rageActivated;
    double rageMultiplier;

public:
    BossMob(string name, int level);
    virtual ~BossMob();

    virtual void act(Unit *target) override;

    virtual void activateRage();
    virtual bool isRageActivated() const;

    string getType() override;
};

#endif
