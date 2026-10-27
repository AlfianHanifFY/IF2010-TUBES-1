#ifndef DEMONLORD_HPP
#define DEMONLORD_HPP

#include <iostream>
using namespace std;

#include "../BossMob.hpp"

class DemonLord : public BossMob
{
public:
    DemonLord(int level);
    virtual ~DemonLord();

    virtual void act(Unit *target) override;
};

#endif
