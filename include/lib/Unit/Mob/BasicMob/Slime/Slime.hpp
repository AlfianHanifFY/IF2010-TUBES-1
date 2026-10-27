#ifndef SLIME_HPP
#define SLIME_HPP

#include <iostream>
using namespace std;

#include "../BasicMob.hpp"

class Slime : public BasicMob
{
public:
    Slime(int level);
    virtual ~Slime();

    virtual void act(Unit *target) override;
};

#endif
