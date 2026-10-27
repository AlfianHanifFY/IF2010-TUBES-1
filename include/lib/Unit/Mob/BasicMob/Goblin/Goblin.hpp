#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include <iostream>
using namespace std;

#include "../BasicMob.hpp"
#include "../BasicMob.hpp"

class Goblin : public BasicMob
{
public:
    Goblin(int level);
    virtual ~Goblin();

    virtual void act(Unit *target) override;
};

#endif
