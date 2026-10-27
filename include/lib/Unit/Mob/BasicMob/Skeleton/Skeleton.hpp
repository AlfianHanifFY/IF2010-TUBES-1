#ifndef SKELETON_HPP
#define SKELETON_HPP

#include <iostream>
using namespace std;

#include "../BasicMob.hpp"
#include "../BasicMob.hpp"

class Skeleton : public BasicMob
{
public:
    Skeleton(int level);
    virtual ~Skeleton();

    virtual void act(Unit *target) override;
};

#endif
