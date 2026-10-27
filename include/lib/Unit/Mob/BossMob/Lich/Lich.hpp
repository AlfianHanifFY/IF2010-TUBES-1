#ifndef LICH_HPP
#define LICH_HPP

#include <iostream>
using namespace std;

#include "../BossMob.hpp"

class Lich : public BossMob
{
public:
    Lich(int level);
    virtual ~Lich();

    virtual void act(Unit *target) override;
};

#endif
