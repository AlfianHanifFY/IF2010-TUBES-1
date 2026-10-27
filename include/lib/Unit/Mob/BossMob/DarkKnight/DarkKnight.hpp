#ifndef DARKKNIGHT_HPP
#define DARKKNIGHT_HPP

#include <iostream>
using namespace std;

#include "../BossMob.hpp"

class DarkKnight : public BossMob
{
public:
    DarkKnight(int level);
    virtual ~DarkKnight();

    virtual void act(Unit *target) override;
};

#endif
