#ifndef ORC_HPP
#define ORC_HPP

#include <iostream>
using namespace std;

#include "../BasicMob.hpp"

class Orc : public BasicMob
{
public:
    Orc(int level);
    virtual ~Orc();

    virtual void act(Unit *target) override;
};

#endif
